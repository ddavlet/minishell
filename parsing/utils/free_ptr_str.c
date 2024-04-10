#include "../parsing.h"

void	*free_ptr_str(char **ptr)
{
	ssize_t	i;

	i = 0;
	if (!ptr)
		return (NULL);
	while (ptr[i])
		free(ptr[i++]);
	free(ptr);
	return (NULL);
}
