/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddavlety <ddavlety@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 17:49:26 by ddavlety          #+#    #+#             */
/*   Updated: 2024/02/16 12:38:39 by ddavlety         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_oper	parse_rule(char *txt)
{
	txt++; //we don't search for it from the first char + SEGFAULT protection
	while (*txt)
	{
		if (*(txt - 1) != '\\')
		{
			if (*txt == '|' && *(txt + 1) != '|')
				return (PIPE);
			else if (*txt == '|')
				return (OR);
			else if (*txt == '&' && *(txt + 1) == '&')
				return (AND);
		}
		txt++;
	}
	return (RUN);
}

int	count_commands(char *txt) //here max value of pipes is limited to int. Need protection?
{
	int	count;

	count = 1;
	txt++; //we don't search for it from the first char + SEGFAULT protection
	while (*txt)
	{
		if (*(txt - 1) != '\\') // no need to handle it according to subject
		{
			if (*txt == '|' && *(txt + 1) != '|')
				count++;
			else if (*txt == '|')
				count++;
			else if (*txt == '&' && *(txt + 1) == '&')
				count++;
		}
		txt++;
	}
	return (count);
}

char	*parse_name(char **ptr)
{
	char	*name;
	char	*txt;
	// size_t	i;

	// i = 0;
	txt = *ptr;
	while (*txt == ' ')
		txt++;
	while (*txt) // is the text contain only normal spaces?
	{
		if (ft_isspace(*txt) || ft_isexeption(*txt))
			break ;
		txt++;
	}
	name = ft_substr(*ptr, 0, txt - *ptr);
	txt++;
	*ptr = txt;
	return (name);
}

int	contain_quotations(char *txt)
{
	while (*txt && !ft_isexeption(*txt))
	{
		if (*txt == '\'' || *txt == '\"')
			return (1);
		txt++;
	}
	return (0);
}

char	**parse_args(char **ptr)
{
	char	**args;
	char	*txt;

	txt = *ptr;
	if (contain_quotations(txt))
		; // what to do when we have quotations?
	else
		args = pars_split(txt, ' ');
	while (*txt && !ft_isexeption(*txt))
		txt++;
	if (ft_isexeption(*txt))
		txt++;
	*ptr = txt;
	return (args);
}

void	debug_print(t_pars *com)
{
	ft_printf("\nCommand:\n");
	ft_printf("comand: %s\n", com->name);
	ft_printf("operation code: %d\n", com->operat);
	int	i = 0;
	while ((com->args)[i])
		ft_printf("arguments: %s\n", (com->args)[i++]);
}

t_pars	*init_comand(char **txt, int i)
{
	t_pars	*com;
	// char	*ptr;

	// ptr = *txt;
	(void)i;
	com = (t_pars *)malloc(sizeof(t_pars));
	com->name = parse_name(txt);
	com->operat = parse_rule(*txt);
	com->args = parse_args(txt);
	// debug_print(com);
	return (com);
}

t_pars	**parse_text(char *txt)
{
	t_pars	**comands;
	int		count; //assume that number of command are less then int
	int		i;

	count = count_commands(txt);
	comands = (t_pars **)malloc(sizeof(t_pars *) * (count + 1));
	comands[count] = NULL;
	i = 0;
	while (i < count)
	{
		comands[i] = init_comand(&txt, i);
		i++;
	}
	return (comands);
}


// test purmose main:

void	debug_print_parse(t_pars **commands)
{
	size_t	i;

	i = 0;
	while(commands[i])
		debug_print(commands[i++]);
}

int	main(int argc, char *argv[])
{
	t_pars **commands = parse_text(argv[1]);

	debug_print_parse(commands);
	(void)argc;
	(void)commands;
	return (0);
}
