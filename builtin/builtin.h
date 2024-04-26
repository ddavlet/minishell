/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddavlety <ddavlety@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 13:34:27 by vketteni          #+#    #+#             */
/*   Updated: 2024/04/26 12:07:49 by ddavlety         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "../libft/libft.h"
# include "../parsing/parsing.h"

int		builtin_export(const char **argv, t_env *shell_env);
int		builtin_env(const char **argv, t_env *shell_env);
int		builtin_unset(const char **argv, t_env *shell_env);
int		builtin_pwd(const char **argv, t_env *shell_env);
int		builtin_echo(const char **argv, t_env *shell_env);
int		builtin_cd(const char **argv, t_env *shell_env);
int		builtin_exit(const char **argv, t_cmd2 *cmd, t_env *shell_env);

/*Utils*/
char	*ft_strcdup(const char *s, int c);
int		ft_isnumber(char *str);
char	**init_export_print(t_env *shell_env);

/*Errors*/
int		builtin_err_gen(const char *cmd, const char *msg, const char *path);

#endif
