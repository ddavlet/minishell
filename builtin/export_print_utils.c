/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_print_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddavlety <ddavlety@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 12:07:21 by ddavlety          #+#    #+#             */
/*   Updated: 2024/04/26 12:15:27 by ddavlety         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static char	*strjoin_env(char const *s1, char const *s2)
{
	unsigned int	i;
	unsigned int	j;
	char			*ptr;

	i = 11;
	j = ft_strlen(s1) + 1;
	if (s2)
		j += ft_strlen(s2);
	ptr = (char *)ft_calloc((j + 14), sizeof(char));
	if (!ptr)
		return (0);
	ft_strlcpy(ptr, "declare -x ", 12);
	while (*s1)
		ptr[i++] = *s1++;
	if (s2)
	{
		ptr[i++] = '=';
		ptr[i++] = '"';
		while (*s2)
			ptr[i++] = *s2++;
		ptr[i++] = '"';
	}
	ptr[i] = '\0';
	return (ptr);
}

static char	*add_char(const char *str, char c)
{
	char	*new_str;
	size_t	len;

	len = ft_strlen(str);
	new_str = (char *)ft_calloc(sizeof(char), len + 2);
	ft_strlcpy(new_str, str, len + 1);
	new_str[len] = c;
	return (new_str);
}

static void	gen_envv(t_env *shell_env, char ***envv, const char *name)
{
	t_env	*child;
	char	*tmp;

	child = shell_env->child;
	while (child)
	{
		tmp = add_char(name, child->letter);
		gen_envv(child, envv, tmp);
		free(tmp);
		child = child->next;
	}
	if (!child)
		if (shell_env->exists == true || shell_env->exported == true)
			*envv = append_arr_str(*envv,
					strjoin_env(name, shell_env->content));
}

char	**init_export_print(t_env *shell_env)
{
	char	**envv;

	envv = (char **)ft_calloc(sizeof(char *), 1);
	if (!envv)
		return (NULL);
	gen_envv(shell_env, &envv, "");
	return (envv);
}
