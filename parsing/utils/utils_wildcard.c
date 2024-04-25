/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_wildcard.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddavlety <ddavlety@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 13:29:39 by ddavlety          #+#    #+#             */
/*   Updated: 2024/04/25 21:11:15 by ddavlety         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

static t_tree	*read_directory(void)
{
	DIR				*dir;
	struct dirent	*entry;
	t_tree			*tree;
	char			*tmp;

	tmp = getcwd(NULL, 0); // get_variable_value("PWD", env);
	if (!tmp)
		return (NULL);
	dir = opendir(tmp);
	free(tmp);
	if (!dir)
	{
		ft_putendl_fd("wildcard parsing error", STDERR_FILENO);
		return (NULL);
	}
	tree = (t_tree *)ft_calloc(sizeof(t_tree), 1);
	entry = readdir(dir);
	while (entry)
	{
		if (entry->d_type == 8)
			add_branch(tree, entry->d_name, entry->d_name);
		entry = readdir(dir);
	}
	closedir(dir);
	return (tree);
}

char	**simple_array(const char *element)
{
	char	**arr;

	arr = (char **)ft_calloc(2, sizeof(char *));
	if (!arr)
		return (NULL);
	arr[0] = ft_strdup(element);
	if (!arr[0])
	{
		free(arr);
		return (NULL);
	}
	return (arr);
}

char	***get_wildcard(const char **argv)
{
	char	***argv_expanded;
	int		i;
	t_tree	*tree;

	argv_expanded = (char ***)ft_calloc(ft_arr_len((char **)argv) + 1,
			sizeof(char **));
	tree = read_directory();
	if (!argv_expanded || !tree)
		return (ft_free_ptr(argv_expanded, tree));
	i = -1;
	while (argv[++i])
	{
		if (contains_wildcards(argv[i]))
			find_wildcard(&(argv_expanded[i]), (char *)argv[i], tree);
		else
			argv_expanded[i] = simple_array(argv[i]);
		if (!argv_expanded[i])
		{
			free_array_3d(argv_expanded);
			terminate_tree(tree);
			return (NULL);
		}
	}
	terminate_tree(tree);
	return (argv_expanded);
}
