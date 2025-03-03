#include "../pipex.h"

int main(int ac, char **av, char **env)
{
	Commands	cmds;

	if (ac != 5)
		return (1);

	saul_good_str(&cmds, av, env);
	printf("%s\n", cmds.path[1]);
	printf("%s\n", cmds.cmd_a[0]);
	printf("%s\n", cmds.cmd_b[0]);
	printf("%s\n", cmds.infile);
	printf("%s\n", cmds.outfile);

	seven_million(&cmds, "done\n");
}
