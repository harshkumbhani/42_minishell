/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkumbhan <hkumbhan@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 15:55:14 by cwenz             #+#    #+#             */
/*   Updated: 2023/10/18 13:26:20 by hkumbhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/* -------------------------------- Includes -------------------------------- */

# include "common.h"
# include "pipex_bonus.h"

/* -------------------------------- Typedefs -------------------------------- */

typedef enum s_token
{
	WORD,
	ARG
}	t_token;

typedef struct s_lexer
{
	char			*start;
	t_token			token;
	int				strlen;
	struct s_lexer	*next;
}	t_lexer;


/* --------------------------------- Signals -------------------------------- */

void	setup_signals();

/* -------------------------------- Executor -------------------------------- */
void	executor(char **env);

/* -------------------------------- Built-ins ------------------------------- */

int		cd(char *path);
int		pwd();
int		env(char **env);
void	echo(char *str);

#endif /* MINISHELL_H */