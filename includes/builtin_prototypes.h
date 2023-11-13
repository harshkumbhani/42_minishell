/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_prototypes.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwenz <cwenz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 14:54:06 by cwenz             #+#    #+#             */
/*   Updated: 2023/11/12 15:06:11 by cwenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_PROTOTYPES_H
# define BUILTIN_PROTOTYPES_H

# include "structs.h"

int		cd(t_env **head, char *path);
int		pwd(void);
int		env(t_env *head);
int		echo(char **cmd);
int		export(t_env **head, char **str);
int		unset(t_env **head, const char *key);
void	builtin_exit(t_minishell *minishell);
void	exec_builtins(t_minishell *minishell, int i);
bool	is_cmd_builtin(t_minishell *minishell, int i);

#endif