/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddavlety <ddavlety@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 13:34:39 by vketteni          #+#    #+#             */
/*   Updated: 2024/04/29 15:40:35 by ddavlety         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static int	is_option(const char *arg)
{
	uint32_t	i;

	i = 2;
	while (arg[i])
	{
		if (arg[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int	print_shell_format(const char *literal, int fd)
{
	const char	*ptr_literal;
	int			count;

	count = 0;
	ptr_literal = literal;
	while (*ptr_literal)
	{
		if (ptr_literal && *ptr_literal == '\\')
			ptr_literal++;
		count += ft_putchar_fd(*ptr_literal, fd);
		ptr_literal++;
	}
	return (count);
}

int	builtin_echo(const char **argv, t_env *shell_env)
{
	ssize_t	i;

	(void)shell_env;
	i = 1;
	while (argv[i] && ft_strncmp(argv[i], "-n", 2) == 0)
	{
		if (argv[2] && is_option(argv[i]))
			i++;
		else
			break ;
	}
	while (argv[i])
	{
		print_shell_format(argv[i], STDOUT_FILENO);
		if (argv[i + 1])
			ft_putstr_fd(" ", STDOUT_FILENO);
		i++;
	}
	if (!argv[1] || ft_strncmp(argv[1], "-n", 2))
		ft_putstr_fd("\n", STDOUT_FILENO);
	return (EXIT_SUCCESS);
}
