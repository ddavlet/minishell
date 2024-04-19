/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_argv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddavlety <ddavlety@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 13:28:20 by ddavlety          #+#    #+#             */
/*   Updated: 2024/04/18 14:14:43 by ddavlety         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

void	free_argv(const char **argv)
{
	int	i;

	i = 0;
	while (argv[i])
		free((void *)argv[i++]);
	free((void *)argv);
}
