#include "parsing.h"
#include <stdio.h>

void	debug_print(t_cmd *com)
{
	ft_printf("\nCommand:\n");
	if (com->com)
		ft_printf("Cmd_name: %s\n", com->com);
	ft_printf("Operation code: %d\n", com->operat);
	ft_printf("Priority: %i\n", com->priority);
	int	i = 0;
	if (com->argv)
		while ((com->argv)[i])
			ft_printf("Arguments: %s\n", (com->argv)[i++]);
	ft_printf("Redirections: \n");
	debug_print_redir(com->redirs);
	ft_printf("_________________\n");
}

void	debug_print_cmd(t_cmd **commands)
{
	size_t	i;

	i = 0;
	if (!commands)
	{
		ft_printf("Commands do not exist");
		return ;
	}
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

void	debug_print_redir(t_redir	*redir)
{
	t_redir	*tmp;

	tmp = redir;
	while (tmp)
	{
		ft_printf("symbol: %i\n", tmp->redir_sym);
		ft_printf("name: %s\n", tmp->redir_name);
		tmp = tmp->next;
	}
}
