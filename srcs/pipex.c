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

void pipe_infile(t_pipex *cmds)
{
	pid_t	pid;
	int		fd;

	pid = fork();
	if (!pid)
	{

	}
}

int main(int ac, char **av, char **env)
{
	t_pipex	cmds;

	if (ac != 5)
		return (1);

	saul_good_str(&cmds, av, env);
	pipe(cmds.pipe_fds);
	
//	printf("%s\n", cmds.path[1]);
//	printf("%s\n", cmds.cmd_a[0]);
//	printf("%s\n", cmds.cmd_b[0]);
//	printf("%s\n", cmds.infile);
//	printf("%s\n", cmds.outfile);

	seven_million(&cmds, "done\n");
}
