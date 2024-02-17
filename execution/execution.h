
#ifndef EXECUTION_H
# define EXECUTION_H

# include "../parsing/parsing.h"
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>


int	execution(t_pars **cmd_arr);

#endif