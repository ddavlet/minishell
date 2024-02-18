#include "parsing.h"
#include <stdio.h>

void	debug_print(t_com *com)
{
	ft_printf("\nCommand:\n");
	ft_printf("comand: %s\n", com->com);
	ft_printf("operation code: %d\n", com->operat);
	int	i = 0;
	while ((com->args)[i])
		ft_printf("arguments: %s\n", (com->args)[i++]);
}

void	debug_print_come(t_com **commands)
{
	size_t	i;

	i = 0;
	while (commands[i])
		debug_print(commands[i++]);
}

void	debug_print_tokens(char **tokens)
{
	int	i;

	i = -1;
	while (tokens[++i])
		ft_printf("token %d: %s\n", i, tokens[i]);
}
