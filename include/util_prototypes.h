/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_prototypes.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkumbhan <hkumbhan@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 12:38:15 by hkumbhan          #+#    #+#             */
/*   Updated: 2023/11/26 12:38:17 by hkumbhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTIL_PROTOTYPES_H
# define UTIL_PROTOTYPES_H

# include "structs.h"

/* ---------------------------------- Utils --------------------------------- */

char	*strjoin_pipex(char *s1, char *s2);
void	copy_std_fds(t_minishell *minishell);
void	reset_fds(t_minishell *minishell);
void	add_pid(t_minishell *minishell, int pid);
void	free_pids(t_minishell *minishell);
t_pids	*find_pid(t_minishell *minishell, int pid);

/* -------------------------------- Env Utils ------------------------------- */

t_env	*find_env_key(t_env *head, char *key);
int		add_env_node(t_env **head, char *key, char *full_string, char *value);
void	print_env_ascending(t_env *head);
void	remove_key(char *key, t_env **head);
void	process_string(t_env **head, char *str);
void	copy_env_variables(t_env **head, char **envp);
int		count_env_variables(t_env *head);
char	**copy_env(t_env *head);

/* -------------------------------- Lst-utils ------------------------------- */

void	lst_add_back(t_lexer **head, t_lexer *new_node);
void	free_lexer(t_lexer **lexer);
void	print_list(t_lexer **head);

#endif