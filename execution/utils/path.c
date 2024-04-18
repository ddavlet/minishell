/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vketteni <vketteni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 13:29:05 by vketteni          #+#    #+#             */
/*   Updated: 2024/04/18 14:06:45 by vketteni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

char	*build_path_from_env(char *name, t_env *env)
{
	char	*all_path;
	char	**env_paths;
	char	*path;
	char	*executable_path;
	int		i;

	all_path = get_variable_value("PATH", env);
	env_paths = ft_split(all_path, ':');
	free(all_path);
	if (!env_paths)
		return (NULL);
	i = -1;
	while (env_paths[++i])
	{
		path = ft_strjoin(env_paths[i], "/");
		executable_path = ft_strjoin_free(path, name);
		if (access(executable_path, F_OK | X_OK) == 0)
		{
			free_arr2d((void **)env_paths);
			return (executable_path);
		}
		free(executable_path);
	}
	free_arr2d((void **)env_paths);
	return (NULL);
}
