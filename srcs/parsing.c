#include "../pipex.h"

static	check_cmds(Commands *cmds)
{
	
}

bool	saul_good_str(Commands *cmds, char **av, char **env)
{
	int	i;
	
	i = 0;
	while(env[i++])
		if (ft_strncmp("PATH=", env[i], 5) == false)
			break ;
	cmds->path = ft_split((env[i] + 5), ':');
	cmds->infile = ft_strdup(av[1]);
	cmds->outfile = ft_strdup(av[4]);
	cmds->cmd_a = ft_split(av[2], ' ');
	cmds->cmd_b = ft_split(av[3], ' ');
	if (!cmds->path || !cmds->infile || !cmds->outfile ||
		!cmds->cmd_a ||!cmds->cmd_b)
		seven_million(cmds, NULL);
	check_cmds(cmds);


	return (true);
}
