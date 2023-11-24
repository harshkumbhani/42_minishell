/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_prototypes.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwenz <cwenz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 14:47:43 by cwenz             #+#    #+#             */
/*   Updated: 2023/11/24 18:05:27 by cwenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_PROTOTYPES_H
# define PARSER_PROTOTYPES_H

# include "structs.h"

/* ---------------------------------- Lexer --------------------------------- */

t_lexer	*tokenise(char *input);
int		token_word(t_lexer **head, char *str);
int		token_pipe(t_lexer **head, char *str);
int		token_squote(t_lexer **head, char *str);
int		token_dquote(t_lexer **head, char *str);
int		token_backslash(t_lexer **head, char *str);
int		create_less(t_lexer **head, char *str);
int		create_greater(t_lexer **head, char *str);
int		create_dbless(t_lexer **head, char *str);
int		create_dbgreater(t_lexer **head, char *str);

/* --------------------------------- Parser --------------------------------- */

int		parser(t_lexer **lexer, t_minishell *minishell);
void	put_args(t_cmd **cmd_table, t_lexer **lexer, t_minishell *minishell);
int		count_pipes(t_lexer **lexer);
int		t_check(t_token token_type);
void	init_t_cmd(t_cmd **cmd);
void	free_cmd_table(t_cmd **cmd_table);
int		is_redirect(t_lexer *lexer);
int		count_words(t_lexer **lexer);
char	*expander(char *str, int strlen,t_minishell *minishell);
void	print_cmd_table(t_cmd **cmd_table);
int		syntax_checker(t_lexer **lexer);
void	redir_add_back(t_redir	**head, t_redir *new_node);
void	hd_add_back(t_heredoc **head, t_heredoc *new);
void	move_and_free(t_lexer **lexer);

/* EXPANDER */

int	check_var(char c);
int	special_var(char **ret, t_minishell *minishell);
int	special_char(char **ret, char *str);

#endif
