/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frey-gal <frey-gal@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 18:56:00 by frey-gal          #+#    #+#             */
/*   Updated: 2025/03/04 18:59:53 by frey-gal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft/libft.h"
# include "libft/ft_printf.h"
# include "libft/get_next_line.h"
# include <unistd.h>
# include <stdbool.h>
# include <stdlib.h>
# include <limits.h>
# include <fcntl.h>
# include <stdio.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>

typedef struct s_pipex
{
	char	**path;
	char	**cmd_a;
	char	**cmd_b;
	char	*infile;
	char	*outfile;
	int		infile_fd;
	int		outfile_fd;
	int		pipe_fds[2];
} t_pipex;

//parsing.c
bool	saul_good_str(t_pipex *cmds, char **av, char **env);

//freeing.c
void	seven_million(t_pipex *cmds, char *error);

#endif
