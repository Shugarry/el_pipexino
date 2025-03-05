/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frey-gal <frey-gal@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 18:56:08 by frey-gal          #+#    #+#             */
/*   Updated: 2025/03/04 18:59:19 by frey-gal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

int	pipe_infile(t_pipex *cmds, char **env)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		seven_million(cmds, strerror(errno), EXIT_FAILURE);
	if (pid == 0)
	{
		dup2(cmds->infile_fd, STDIN_FILENO);
		dup2(cmds->pipe_fds[1], STDOUT_FILENO);
		close(cmds->infile_fd);
		close(cmds->pipe_fds[0]);
		execve(cmds->cmd_a[0], cmds->cmd_a, env);
		exit(EXIT_SUCCESS);
	}
	close(cmds->pipe_fds[1]);
	return (pid);
}

int	pipe_outfile(t_pipex *cmds, char **env)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		seven_million(cmds, strerror(errno), EXIT_FAILURE);
	if (pid == 0)
	{
		dup2(cmds->pipe_fds[0], STDIN_FILENO);
		dup2(cmds->outfile_fd, STDOUT_FILENO);
		close(cmds->pipe_fds[1]);
		execve(cmds->cmd_b[0], cmds->cmd_a, env);
		exit(EXIT_SUCCESS);
	}
	close(cmds->pipe_fds[0]);
	close(cmds->outfile_fd);
	return (pid);
}

int	main(int ac, char **av, char **env)
{
	t_pipex	cmds;
	int		pid[2];
	int		wait_status[2];

	if (ac != 5)
		return (1);
	saul_good_str(&cmds, av, env);
	if (pipe(cmds.pipe_fds) == -1)
		seven_million(&cmds, strerror(errno), EXIT_FAILURE);
	pid[0] = pipe_infile(&cmds, env);
	pid[1] = pipe_outfile(&cmds, env);
	if (pid[0])
		waitpid(pid[0], &wait_status[0], 0);
	else
		close(cmds.pipe_fds[1]);
	waitpid(pid[1], &wait_status[1], 0);
	if (WIFEXITED(wait_status[1]))
		seven_million(&cmds, NULL, wait_status[1]);
}
