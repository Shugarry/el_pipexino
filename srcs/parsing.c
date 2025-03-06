/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frey-gal <frey-gal@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 18:56:07 by frey-gal          #+#    #+#             */
/*   Updated: 2025/03/06 23:31:21 by frey-gal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

// Parses and checks whether command a is an executable command by looking in
// program root directory and through PATH. Replaces the command for full path
// if found. Erroneous command is automatically handled later by execve()
static void	check_cmd_a(t_pipex *cmds, int i)
{
	char	*command;
	char	*tmp;

	while (cmds->path[i])
	{
		tmp = ft_strjoin(cmds->path[i], "/");
		if (!tmp)
			free_exit(cmds, "malloc failure", EXIT_FAILURE);
		command = ft_strjoin(tmp, cmds->cmd_a[0]);
		free(tmp);
		if (!command)
			free_exit(cmds, "malloc failure", EXIT_FAILURE);
		if (access(command, X_OK) == 0)
		{
			free(cmds->cmd_a[0]);
			cmds->cmd_a[0] = ft_strdup(command);
			free(command);
			return ;
		}
		free(command);
		i++;
	}
	if (access(cmds->cmd_a[0], X_OK) == 0)
		return ;
}

// Same for command b
static void	check_cmd_b(t_pipex *cmds, int i)
{
	char	*command;
	char	*tmp;

	while (cmds->path[i])
	{
		tmp = ft_strjoin(cmds->path[i], "/");
		if (!tmp)
			free_exit(cmds, "malloc failure", EXIT_FAILURE);
		command = ft_strjoin(tmp, cmds->cmd_b[0]);
		free(tmp);
		if (!command)
			free_exit(cmds, "malloc failure", EXIT_FAILURE);
		if (access(command, X_OK) == 0)
		{
			free(cmds->cmd_b[0]);
			cmds->cmd_b[0] = ft_strdup(command);
			free(command);
			return ;
		}
		free(command);
		i++;
	}
	if (access(cmds->cmd_b[0], X_OK) == 0)
		return ;
}

// Checks for validity of files, whether they exist or can be opened/read/write
// On error, exits with error message
static void	check_files(t_pipex *cmds)
{
	cmds->infile_fd = -1;
	cmds->outfile_fd = -1;
	cmds->infile_fd = open(cmds->infile, O_RDONLY);
	if (cmds->infile_fd == -1 || access(cmds->infile, R_OK) == -1)
		free_exit(cmds, "open() failure", EXIT_SUCCESS);
	cmds->outfile_fd = open(cmds->outfile, O_CREAT | O_RDWR | O_TRUNC, 0755);
	if (cmds->outfile_fd == -1 || access(cmds->outfile, W_OK) == -1)
		free_exit(cmds, "open() failure", EXIT_FAILURE);
}

static void	init_struct(t_pipex *cmds)
{
	cmds->path = NULL;
	cmds->infile = NULL;
	cmds->outfile = NULL;
	cmds->cmd_a = NULL;
	cmds->cmd_b = NULL;
}

// Initializes and parses every command/file path necessary in the t_pipex
// struct
void	parser(t_pipex *cmds, char **av, char **env)
{
	int	i;

	i = 0;
	while (env[i++] != NULL)
		if (ft_strncmp("PATH=", env[i], 5) == false)
			break ;
	init_struct(cmds);
	cmds->path = ft_split((env[i] + 5), ':');
	cmds->infile = ft_strdup(av[1]);
	cmds->outfile = ft_strdup(av[4]);
	cmds->cmd_a = ft_split(av[2], ' ');
	cmds->cmd_b = ft_split(av[3], ' ');
	if (cmds->cmd_a && cmds->cmd_a[0])
		check_cmd_a(cmds, 0);
	if (cmds->cmd_b && cmds->cmd_b[0])
		check_cmd_b(cmds, 0);
	check_files(cmds);
}
