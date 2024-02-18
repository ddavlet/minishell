
#include "execution.h"

int	execution(t_pars **cmd_arr, char *envp[])
{

	
	
}

int	main(int argc, char *argv[], char *envp[])
{
	// t_pars	**commands = parse_text(argv[1]);
	t_com	**commands = parse_text("ls -l | grep .c | wc -l");

	debug_print_parse(commands);
	execution(commands, envp);

	(void)argc;
	(void)argv;
	return (0);
}
