/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwenz <cwenz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 15:01:33 by cwenz             #+#    #+#             */
/*   Updated: 2023/11/16 15:27:13 by cwenz            ###   ########.fr       */
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
void	block_signal(void);
void	setup_child_signals(void);
void	setup_heredoc_signals(void);

void	free_env_linked_list(t_env	*head);
void	free_env_node(t_env *node);
void	free_env_array(char **envp);
void	error_msg(char *cmd, char *cmd2, char *reason);

#endif