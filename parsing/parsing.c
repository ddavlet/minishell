/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddavlety <ddavlety@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 17:49:26 by ddavlety          #+#    #+#             */
/*   Updated: 2024/02/14 18:50:32 by ddavlety         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_oper	retn_rule(char *txt)
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

	count = 0;
	txt++; //we don't search for it from the first char + SEGFAULT protection
	while (*txt)
	{
		if (*(txt - 1) != '\\')
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
}

size_t	count_len(char *txt)
{

}

char	*parse_name(char **txt)
{
	char *name;

	while (**txt) // is the text contain only normal spaces?
	{
		if (ft_isspace(**txt))
			break ;

		*txt++;
	}
}

t_pars	*init_comand(char **txt)
{
	t_pars	*com;
	char	*ptr;

	// ptr = *txt;
	com = (t_pars *)malloc(sizeof(t_pars));
	com->name = parse_name(txt, );
}

t_pars	*parse_text(char *txt)
{
	t_pars	**comands;
	int		count;

	count = count_commands(txt);
	comands = (t_pars **)malloc(sizeof(t_pars *) * (count + 1));
	comands[count] = NULL;

	while (count--)
	{
		comands[count] = init_comand(&txt);
	}
}


// test purmose main:

int	main(void)
{
	char txt[] = "some text";
	t_pars *commands = parse_text(txt);

	return (0);
}
