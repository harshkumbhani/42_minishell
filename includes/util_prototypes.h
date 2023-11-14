/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_prototypes.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwenz <cwenz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 14:57:24 by cwenz             #+#    #+#             */
/*   Updated: 2023/11/14 16:28:18 by cwenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTIL_PROTOTYPES_H
# define UTIL_PROTOTYPES_H

# include "structs.h"

/* ---------------------------------- Utils --------------------------------- */

char	*strjoin_pipex(char *s1, char *s2);
void	copy_std_fds(t_minishell *minishell);
void	reset_fds(t_minishell *minishell);

/* -------------------------------- Env Utils ------------------------------- */

t_env	*find_env_key(t_env *head, char *key);
int		add_env_node(t_env **head, char *key, char *full_string, char *value);
void	print_env_ascending(t_env *head);
void	remove_key(char *key, t_env **head);
void	process_string(t_env **head, char *str);
void	copy_env_variables(t_env **head, char **envp);

/* ------------------------------- File Utils ------------------------------- */

void	open_outfile(t_cmd *cmd);
void	open_infile(t_cmd *cmd);

/* -------------------------------- Lst-utils ------------------------------- */

void	lst_add_back(t_lexer **head, t_lexer *new_node);
void	lst_del(t_lexer **head);
void	print_list(t_lexer **head);

#endif