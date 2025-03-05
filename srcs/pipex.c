/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frey-gal <frey-gal@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 18:56:08 by frey-gal          #+#    #+#             */
/*   Updated: 2025/03/05 21:33:23 by frey-gal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

// Forks process, and returns pid on parent process for waitpid().
// Child process then replaces STD IN/OUT for infile and respective pipe_fd
// and does execve()
int	pipe_infile(t_pipex *cmds, char **env)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		seven_million(cmds, "fork failure", EXIT_FAILURE);
	if (pid == 0)
	{
		if (dup2(cmds->infile_fd, STDIN_FILENO) == -1
			|| dup2(cmds->pipe_fds[WR_END], STDOUT_FILENO) == -1)
		{
			fd_cleaner(cmds);
			seven_million(cmds, "dup2 failure", EXIT_FAILURE);
		}
		fd_cleaner(cmds);
		if (execve(cmds->cmd_a[0], cmds->cmd_a, env) == -1)
			seven_million(cmds, "execve failure", EXIT_FAILURE);
	}
	return (pid);
}

// Similar to pipe_infile() but swapping reads/writes ins/outs. Also returns
// pid for waitpid()
int	pipe_outfile(t_pipex *cmds, char **env)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		seven_million(cmds, "fork failure", EXIT_FAILURE);
	if (pid == 0)
	{
		if (dup2(cmds->pipe_fds[RD_END], STDIN_FILENO) == -1
			|| dup2(cmds->outfile_fd, STDOUT_FILENO) == -1)
		{
			fd_cleaner(cmds);
			seven_million(cmds, "dup2 failure", EXIT_FAILURE);
		}
		fd_cleaner(cmds);
		if (execve(cmds->cmd_b[0], cmds->cmd_b, env) == -1)
			seven_million(cmds, "execve failure", EXIT_FAILURE);
	}
	return (pid);
}

int	main(int ac, char **av, char **env)
{
	t_pipex	cmds;
	int		pid[2];
	int		wait_status[2];

	wait_status[0] = 0;
	wait_status[1] = 0;
	if (ac != 5)
		return (1);
	saul_good_str(&cmds, av, env);
	if (pipe(cmds.pipe_fds) == -1)
		seven_million(&cmds, "pipe failure", EXIT_FAILURE);
	pid[0] = pipe_infile(&cmds, env);
	pid[1] = pipe_outfile(&cmds, env);
	fd_cleaner(&cmds);
	if (waitpid(pid[0], &wait_status[0], 0) == -1)
		seven_million(&cmds, "waitpid failure", EXIT_FAILURE);
	if (WIFEXITED(wait_status[0]) && WEXITSTATUS(wait_status[0]))
		seven_million(&cmds, "subprocess failure", WEXITSTATUS(wait_status[0]));
	if (waitpid(pid[1], &wait_status[0], 0) == -1)
		seven_million(&cmds, "waitpid failure", EXIT_FAILURE);
	if (WIFEXITED(wait_status[1]) && WEXITSTATUS(wait_status[1]))
		seven_million(&cmds, "subprocess failure", WEXITSTATUS(wait_status[1]));
	seven_million(&cmds, NULL, EXIT_SUCCESS);
}
