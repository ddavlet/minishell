/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_pars.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddavlety <ddavlety@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 15:07:44 by ddavlety          #+#    #+#             */
/*   Updated: 2024/03/24 07:28:13 by ddavlety         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

char	*operation(t_oper type)
{
	char	*types[5];

	types[0] = NULL;
	types[1] = "\\|";
	types[2] = "\\&";
	types[3] = "\\||";
	types[4] = "\\&&";
	if (type == RUN)
		return (NULL);
	return (ft_strdup(types[type]));
}

size_t	ft_arr_cpy(char **dst, char **src, size_t *pos)
{
	while (*src)
		dst[(*pos)++] = ft_strdup(*src++);
	return (*pos);
}

char	**reverse_pars(t_cmd **cmds_tojoin, int commands)
{
	char	**argv;
	size_t	len;
	int		i;

	i = 0;
	len = 0;
	while (i < commands)
		len += ft_arr_len(cmds_tojoin[i++]->argv);
	argv = (char **) ft_calloc(sizeof(char *), len + commands + 1);
	i = 0;
	len = 0;
	while (i < commands)
	{
		ft_arr_cpy(argv, cmds_tojoin[i]->argv, &len);
		argv[len++] = operation(cmds_tojoin[i]->operat);
		i++;
	}
	return (argv);
}
