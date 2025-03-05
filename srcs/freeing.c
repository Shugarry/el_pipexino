#include "../pipex.h"

// Frees each element of the char **str
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

// function that frees everything and exits the program
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
// TODO: close fds for pipe and others if necessary
