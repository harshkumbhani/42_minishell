/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwenz <cwenz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 14:32:49 by cwenz             #+#    #+#             */
/*   Updated: 2023/11/12 15:02:43 by cwenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include "includes.h"

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

typedef struct s_cmd {
	char	**cmd;
	char	*deli;
	char	*infile;
	char	*outfile;
	int		infile_fd;
	int		outfile_fd;
	int		file_type;
	bool	here_doc;
}	t_cmd;

typedef struct s_stdfds
{
	int	stdin;
	int	stdout;
}	t_stdfds;

typedef struct s_minishell {
	t_cmd		**cmd_table;
	int			exit_code;
	int			fd[2];
	t_stdfds	stdfds;
	t_env		*head_env;
}	t_minishell;

#endif