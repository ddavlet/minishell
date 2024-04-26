/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vketteni <vketteni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 13:28:14 by ddavlety          #+#    #+#             */
/*   Updated: 2024/04/26 13:51:57 by vketteni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

const char	*get_variable_name(const char *dollar_sign)
{
	size_t	len;

	if (!dollar_sign)
		return (NULL);
	dollar_sign++;
	len = 1;
	while (ft_isalnum(*(dollar_sign + len)) || *(dollar_sign + len) == '_')
		len++;
	return (ft_substr(dollar_sign, 0, len));
}

char	*get_variable_value(const char *name, t_env *shell_env)
{
	t_env	*child;

	if (!name)
		return (NULL);
	child = shell_env->child;
	while (child)
	{
		if (child->letter == *name && *(name + 1))
		{
			child = child->child;
			name++;
		}
		else if (child->letter == *name && !*(name + 1))
		{
			if (child->exists == true)
				return (ft_strdup(child->content));
			else
				return (ft_strdup(""));
		}
		else
			child = child->next;
	}
	return (ft_strdup(""));
}

char	*get_shell_variable(const char *dollar_sign, const char *literal,
		t_env *shell_env)
{
	const char	*name;
	char		*value;

	if (!dollar_sign || !literal || !shell_env)
		return (NULL);
	if (*(dollar_sign + 1) == '?')
		value = get_variable_value("LAST_EXIT_STATUS", shell_env);
	else
	{
		name = get_variable_name(dollar_sign);
		value = get_variable_value(name, shell_env);
		free((char *)name);
	}
	return (value);
}
