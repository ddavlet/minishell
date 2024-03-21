#include "execution.h"

void	initialize_status_codes(t_executor *exec)
{
	int i;
	int *status_codes;

	
	status_codes = (int *)ft_calloc(exec->size + 1, sizeof(int));
    if (!status_codes)
    {
        terminate(exec, EXIT_FAILURE, "error");
    }
	i = 0;
	while (i < exec->size)
		status_codes[i++] = -1;
    exec->status_codes = status_codes;
}
