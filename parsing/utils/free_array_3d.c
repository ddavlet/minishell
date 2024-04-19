/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_array_3d.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddavlety <ddavlety@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 13:28:23 by ddavlety          #+#    #+#             */
/*   Updated: 2024/04/18 13:28:23 by ddavlety         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

void	free_array_3d(char ***arr_3d)
{
	int	i;
	int	j;

	i = 0;
	while (arr_3d[i])
	{
		j = 0;
		while (arr_3d[i][j])
			free(arr_3d[i][j++]);
		free(arr_3d[i++]);
	}
	free(arr_3d);
}
