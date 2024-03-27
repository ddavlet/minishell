#include "parsing.h"

int	id_gen(int seed)
{
	seed = (1103515245 * seed + 12345) % 2147483648;
	return (seed);
}
