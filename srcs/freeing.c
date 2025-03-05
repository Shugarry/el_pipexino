/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freeing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frey-gal <frey-gal@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 17:09:11 by frey-gal          #+#    #+#             */
/*   Updated: 2025/03/05 20:48:11 by frey-gal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

// Safely frees each element of the char* array (from ft_split)
static void	split_free(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

// Checks if fds are open and cleans them to prevent hanging fds
void	fd_cleaner(t_pipex *cmds)
{
	if (cmds->pipe_fds[0])
		close(cmds->pipe_fds[0]);
	if (cmds->pipe_fds[1])
		close(cmds->pipe_fds[1]);
	if (cmds->infile_fd)
		close(cmds->infile_fd);
	if (cmds->outfile_fd)
		close(cmds->outfile_fd);
}

// Safely frees infile and outfile strings, prints error message if present and
// exits program
void	seven_million(t_pipex *cmds, char *error, int exit_status)
{
	if (cmds->infile)
		free(cmds->infile);
	if (cmds->outfile)
		free(cmds->outfile);
	split_free(cmds->path);
	split_free(cmds->cmd_a);
	split_free(cmds->cmd_b);
	if (error)
		perror(error);
	exit(exit_status);
}
