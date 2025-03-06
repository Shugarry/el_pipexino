/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frey-gal <frey-gal@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 18:56:08 by frey-gal          #+#    #+#             */
/*   Updated: 2025/03/06 23:30:57 by frey-gal         ###   ########.fr       */
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
		free_exit(cmds, "fork failure", EXIT_FAILURE);
	if (pid == 0)
	{
		if (dup2(cmds->infile_fd, STDIN_FILENO) == -1
			|| dup2(cmds->pipe_fds[WR_END], STDOUT_FILENO) == -1)
			perror("dup2 failure");
		close(cmds->pipe_fds[RD_END]);
		in_out_cleaner(cmds);
		if (cmds->cmd_a[0] && cmds->cmd_a[0][0])
			execve(cmds->cmd_a[0], cmds->cmd_a, env);
		else
			free_exit(cmds, "execve failure", 126);
		if (errno == ENOENT)
			free_exit(cmds, "execve failure", 127);
		else
			free_exit(cmds, "execve failure", EXIT_FAILURE);
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
		free_exit(cmds, "fork failure", EXIT_FAILURE);
	if (pid == 0)
	{
		if (dup2(cmds->pipe_fds[RD_END], STDIN_FILENO) == -1
			|| dup2(cmds->outfile_fd, STDOUT_FILENO) == -1)
			perror("dup2 failure");
		close(cmds->pipe_fds[WR_END]);
		in_out_cleaner(cmds);
		if (cmds->cmd_b[0] && cmds->cmd_b[0][0])
			execve(cmds->cmd_b[0], cmds->cmd_b, env);
		else
			free_exit(cmds, "execve failure", 126);
		if (errno == ENOENT)
			free_exit(cmds, "execve failure", 127);
		else
			free_exit(cmds, "execve failure", EXIT_FAILURE);
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
	if (pipe(cmds.pipe_fds) == -1)
		free_exit(&cmds, "pipe failure", EXIT_FAILURE);
	parser(&cmds, av, env);
	pid[0] = pipe_infile(&cmds, env);
	pid[1] = pipe_outfile(&cmds, env);
	if (waitpid(pid[0], &wait_status[0], 0) == -1)
		free_exit(&cmds, "waitpid failure", EXIT_FAILURE);
	close(cmds.pipe_fds[WR_END]);
	if (waitpid(pid[1], &wait_status[1], 0) == -1)
		free_exit(&cmds, "waitpid failure", EXIT_FAILURE);
	close(cmds.pipe_fds[RD_END]);
	if (WIFEXITED(wait_status[0]) && WEXITSTATUS(wait_status[0]))
		free_exit(&cmds, "subprocess failure", WEXITSTATUS(wait_status[0]));
	if (WIFEXITED(wait_status[1]) && WEXITSTATUS(wait_status[1]))
		free_exit(&cmds, "subprocess failure", WEXITSTATUS(wait_status[1]));
	free_exit(&cmds, NULL, EXIT_SUCCESS);
}
