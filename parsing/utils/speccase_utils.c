/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   speccase_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddavlety <ddavlety@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 13:29:28 by ddavlety          #+#    #+#             */
/*   Updated: 2024/04/18 13:29:29 by ddavlety         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

static int	spec_case(char c)
{
	if (c == '?')
		return (1);
	else if (c == '$')
		return (2);
	else if (c == '0')
		return (3);
	else if (ft_isdigit(c))
		return (4);
	else
		return (0);
}

static char	*case_handler(int key, t_env *shell_env)
{
	(void)shell_env;
	if (key == 1)
		return (ft_strdup("exit_code"));
	if (key == 2)
		return (ft_itoa(getpid()));
	if (key == 3)
		return (ft_strdup("minishell"));
	if (key == 4)
		return (ft_strdup(""));
	else
		return (NULL);
}

char	*get_case(char *literal, t_env *shell_env)
{
	char		*new;
	char		*tmp;
	const char	*dollar_sign;

	dollar_sign = find_variable(literal);
	if (!dollar_sign)
		return (NULL);
	new = ft_substr(literal, 0, dollar_sign - literal);
	if (!new)
		return (NULL);
	tmp = case_handler(spec_case(*(dollar_sign + 1)), shell_env);
	if (!tmp)
	{
		free(new);
		return (NULL);
	}
	new = ft_strjoin_free(new, tmp);
	free(tmp);
	new = ft_strjoin_free(new, dollar_sign + 2);
	return (new);
}

int	is_special_case(const char *literal)
{
	const char	*ptr_variable;

	ptr_variable = find_variable(literal);
	if (!ptr_variable)
		return (0);
	if (spec_case(*(ptr_variable + 1)))
		return (1);
	return (0);
}
