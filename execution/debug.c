#include "../libft/libft.h"
#include "execution.h"
#include <stdlib.h>
#include <string.h> // For memcpy
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>



int	main(int argc, char *argv[],const char *envp[])
{
	t_cmd **cmds;

	(void)argc;
	(void)argv;
	t_env *env = init_env((const char **)envp);

	cmds = parse_text("echo", env);
		// wildcard parsing error: No such file or directory
	execution(cmds, (char **)envp);
	return (0);
}
