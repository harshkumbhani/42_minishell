/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkumbhan <hkumbhan@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 15:55:14 by cwenz             #+#    #+#             */
/*   Updated: 2023/10/17 11:05:30 by hkumbhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/* -------------------------------- Includes -------------------------------- */

# include "common.h"
# include "pipex_bonus.h"

/* -------------------------------- Typedefs -------------------------------- */

typedef struct s_minilist
{
	
}	t_minilist;

typedef struct s_lexer
{
	
}	t_lexer;

typedef enum s_token
{
	WORD,
	ARG
}	t_token;

/* --------------------------------- Signals -------------------------------- */

void	setup_signals();

/* -------------------------------- Built-ins ------------------------------- */

int		cd(char *path);
int		pwd();

#endif /* MINISHELL_H */