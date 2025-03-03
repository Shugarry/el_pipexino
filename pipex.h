#ifndef PIPEX_H
# define PIPEX_H

# include "libft/libft.h"
#include "libft/ft_printf.h"
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

typedef struct
{
	char	**path;
	char	**cmd_a;
	char	**cmd_b;
	char	*infile;
	char	*outfile;
} Commands;

//parsing.c
bool	saul_good_str(Commands *cmds, char **av, char **env);

//freeing.c
void	seven_million(Commands *cmds, char *error);

#endif
