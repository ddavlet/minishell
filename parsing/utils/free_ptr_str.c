/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_ptr_str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddavlety <ddavlety@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 13:28:35 by ddavlety          #+#    #+#             */
/*   Updated: 2024/04/18 13:28:36 by ddavlety         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

void	*free_ptr_str(char **ptr)
{
	ssize_t	i;

	i = 0;
	if (!ptr)
		return (NULL);
	while (ptr[i])
		free(ptr[i++]);
	free(ptr);
	return (NULL);
}
