/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_prototypes.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwenz <cwenz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 14:52:11 by cwenz             #+#    #+#             */
/*   Updated: 2023/11/12 14:54:51 by cwenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_PROTOTYPES_H
# define EXECUTOR_PROTOTYPES_H

# include "structs.h"

void	executor(t_minishell *minishell);
void	execute_cmd(t_cmd *cmds, t_env *head_env);
void	execute_cmd_with_pipe(t_minishell *minishell, int index);
void	execute_final_cmd(t_minishell *minishell, int index);
void	get_exit_status(t_minishell *minishell);
void	execute_child_with_pipe(t_minishell *minishell, int index);
void	handle_cmd_execution(t_minishell *minishell, int index);
void	handle_heredoc(t_minishell *minishell, int index);
char	*find_cmd_path(t_cmd *cmd, char **envp);

#endif