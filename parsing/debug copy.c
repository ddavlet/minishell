#include "../libft/libft.h"
#include "parsing.h"
#include <stdlib.h>
#include <string.h> // For memcpy
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

char	**reverse_pars(t_cmd **cmds_tojoin, int commands);

int	main(int argc, char *argv[],const char *envp[])
{
	t_cmd **cmds;

	(void)argc;
	(void)argv;
	t_env *env = init_env((const char **)envp);
	cmds = parse_text("echo test | echo test2 || echo test 3", env);
	debug_print_array_strings(reverse_pars(cmds, 3));
	return (0);
}
