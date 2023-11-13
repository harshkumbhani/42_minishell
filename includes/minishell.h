/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkumbhan <hkumbhan@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 15:01:33 by cwenz             #+#    #+#             */
/*   Updated: 2023/11/13 10:44:01 by hkumbhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "includes.h"
# include "structs.h"
# include "parser_prototypes.h"
# include "executor_prototypes.h"
# include "builtin_prototypes.h"
# include "util_prototypes.h"

void	setup_signals(void);

void	free_env_linked_list(t_env	*head);
void	free_env_node(t_env *node);
void	free_env_array(char **envp);
void	error_msg(char *cmd, char *reason);

#endif