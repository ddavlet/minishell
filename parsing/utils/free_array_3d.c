#include "../parsing.h"

void	free_array_3d(char ***arr_3d)
{
	int	i;
	int	j;

	i = 0;
	while (arr_3d[i])
	{
		j = 0;
		while (arr_3d[i][j])
			free(arr_3d[i][j++]);
		free(arr_3d[i++]);
	}
	free(arr_3d);
}
