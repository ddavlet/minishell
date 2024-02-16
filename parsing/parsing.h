/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddavlety <ddavlety@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 17:48:42 by ddavlety          #+#    #+#             */
/*   Updated: 2024/02/15 20:01:00 by ddavlety         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "../libft/libft.h"
# include <unistd.h>
# include <signal.h>
# include <stdio.h>
# include <string.h>
# include <stdbool.h>

typedef enum e_oper {
	RUN,
	PIPE,
	OR,
	AND,
}			t_oper;

typedef struct s_pars
{
	char			*name;
	bool			ligit;
	enum e_oper		operat;
	char			**args;
	// struct s_pars	*next;
}					t_pars;

/*Utils*/
char	**pars_split(char const *s, char c);
int		ft_isexeption(char c);

#endif
