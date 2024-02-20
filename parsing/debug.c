#include "parsing.h"
#include <stdio.h>

void	debug_print(t_cmd *com)
{
	ft_printf("\nCommand:\n");
	ft_printf("comand: %s\n", com->com);
	ft_printf("operation code: %d\n", com->operat);
	int	i = 0;
	while ((com->argv)[i])
		ft_printf("arguments: %s\n", (com->argv)[i++]);
}

void	debug_print_cmd(t_cmd **commands)
{
	size_t	i;

	i = 0;
	while (commands[i])
		debug_print(commands[i++]);
}

void	debug_print_array_strings(char **tokens)
{
	int	i;

	i = -1;
	while (tokens[++i])
		ft_printf("String %d: %s\n", i, tokens[i]);
}

void	debug_print_env(t_env	*root, const char *search)
{
	t_env	*child;

	child = root->child;
	while (child)
	{
		if (child->letter == *search && *(search + 1))
		{
			child = child->child;
			search++;
		}
		else if (child->letter == *search && !*(search + 1))
		{
			if (child->exists == true)
			{
				ft_printf ("%s\n", child->content);
				break ;
			}
			else
			{
				ft_printf ("found, but does not exist\n");
				break ;
			}
		}
		else
			child = child->next;
	}
	if (!child)
		ft_printf ("didn't find anything\n");
}

