#include "parsing.h"
#include <stdio.h>

void	debug_print(t_cmd *com, int fd)
{
	ft_putstr_fd("\nCommand:\n", fd);
	if (com->com)
    {
		ft_putstr_fd("Cmd_name: ", fd);
        ft_putendl_fd(com->com, fd);
    }
	ft_putstr_fd("Operation code: ", fd);
    ft_putendl_fd(ft_itoa(com->operat), fd);

	// for (size_t i = 0; com->scope_stack[i]; i++)
	// 	ft_putstr_fd("Priority: %i\n", com->scope_stack[i], fd);
	int	i = 0;
	if (com->argv)
		while ((com->argv)[i])
        {
			ft_putstr_fd("Arguments: ", fd);
            ft_putendl_fd((com->argv)[i++], fd);
        }
	ft_putstr_fd("Redirections: \n", fd);
	debug_print_redir(com->redirs, fd);
	ft_putstr_fd("_________________\n", fd);
}

void	debug_print_cmds(t_cmd **commands, int fd)
{
	size_t	i;

	i = 0;
	if (!commands)
	{
		ft_printf("Commands do not exist\n");
		return ;
	}
	while (commands[i])
		debug_print(commands[i++], fd);
}

void	debug_print_array_strings(char **tokens)
{
	int	i;

	i = -1;
	while (tokens[++i])
	{
		write(1, "token: ", 7);
		write(1, tokens[i], ft_strlen(tokens[i]));
		write(1, "\n", 1);
		// ft_printf("String %d: %s\n", i, tokens[i]);
	}
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

void	debug_print_redir(t_redir	*redir, int fd)
{
	t_redir	*tmp;

	tmp = redir;
	while (tmp)
	{
		ft_putstr_fd("symbol: ", fd);
		ft_putendl_fd(ft_itoa(tmp->redir_sym), fd);
		ft_putstr_fd("name: ", fd);
		ft_putendl_fd(tmp->redir_name, fd);
		tmp = tmp->next;
	}
}
