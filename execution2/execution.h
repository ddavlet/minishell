
#include "parsing.h"


typedef struct s_exec
{
	int		pipe[2];
	// int		status_code;
	pid_t	pid;
	bool	has_redir_in;
	bool	has_redir_out;
	t_cmd	*cmd;
}			t_exec;
