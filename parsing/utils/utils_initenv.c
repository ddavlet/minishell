/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_initenv.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddavlety <ddavlety@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 13:29:33 by ddavlety          #+#    #+#             */
/*   Updated: 2024/04/18 13:29:34 by ddavlety         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

static char	*strjoin_env(char const *s1, char const *s2)
{
	unsigned int	i;
	unsigned int	j;
	char			*ptr;

	i = 0;
	j = ft_strlen(s1) + ft_strlen(s2) + 1;
	ptr = (char *)ft_calloc((j + 1), sizeof(char));
	if (!ptr)
		return (0);
	while (*s1)
		ptr[i++] = *s1++;
	ptr[i++] = '=';
	while (*s2)
		ptr[i++] = *s2++;
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
		if (shell_env->exists == true)
			*envv = append_arr_str(*envv, strjoin_env(name, shell_env->content));
}

char	**init_envv(t_env *shell_env)
{
	char	**envv;

	envv = (char **)ft_calloc(sizeof(char *), 1); // TODO: protect this
	gen_envv(shell_env, &envv, "");
	return (envv);
}
