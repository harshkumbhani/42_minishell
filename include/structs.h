/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkumbhan <hkumbhan@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 12:36:59 by hkumbhan          #+#    #+#             */
/*   Updated: 2023/11/26 12:37:33 by hkumbhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include "includes.h"

typedef enum e_error
{
	ERR_MEMORY	= 0,
	ERR_PIPE	= 1,
	ERR_FORK	= 2,
}	t_error;

typedef enum e_dstruct
{
	T_LEX		= 1 << 0,
	T_MINI		= 1 << 1
}	t_dstruct;

typedef enum e_token
{
	WORD			= 0,
	PIPE			= 1,
	SQUOTE			= 2,
	DQUOTE			= 3,
	BACKSLASH		= 4,
	LESS			= 5,
	GREATER			= 6,
	DOUBLE_LESS		= 7,
	DOUBLE_GREATER	= 8
}	t_token;

typedef struct s_lexer
{
	char			*start;
	t_token			token;
	int				strlen;
	bool			not_space;
	struct s_lexer	*next;
}	t_lexer;

typedef struct s_env
{
	char			*key;
	char			*value;
	char			*full_string;
	struct s_env	*next;
}	t_env;

typedef struct s_redir
{
	char			*file_name;
	int				file_fd;
	int				file_type;
	struct s_redir	*next;
}	t_redir;

typedef struct s_heredoc
{
	char				*str;
	bool				expand;
	struct s_heredoc	*next;
}	t_heredoc;

typedef struct s_cmd {
	char		**cmd;
	t_heredoc	*heredoc;
	t_redir		*files;
}	t_cmd;

typedef struct s_stdfds
{
	int	stdin;
	int	stdout;
}	t_stdfds;

typedef struct s_pids
{
	int				pid;
	bool			has_checked;
	struct s_pids	*next;
}	t_pids;

typedef struct s_minishell {
	t_cmd		**cmd_table;
	t_pids		*pids;
	int			*exit_code;
	int			fd[2];
	t_stdfds	stdfds;
	t_env		*head_env;
}	t_minishell;

#endif