#include "../execution.h"

void	free_arr2d(void **arr2d)
{
	int	i;
    char **arr;

    arr = (char **)arr2d;
	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

void	msg_error(char *err)
{
	perror(err);
	exit(EXIT_FAILURE);
}


unsigned long	rand_simple(void)
{
	static unsigned long	lcg_prev = 21512345435143;
	const unsigned long		a = 1103515245;
	const unsigned long		c = 12345;
	const unsigned long		m = 1UL << 31; // 2^31

	lcg_prev = (a * lcg_prev + c) % m;
	return (lcg_prev);
}
