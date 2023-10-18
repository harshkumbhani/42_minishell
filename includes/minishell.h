/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwenz <cwenz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 15:55:14 by cwenz             #+#    #+#             */
/*   Updated: 2023/10/17 17:15:51 by cwenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/* -------------------------------- Includes -------------------------------- */

# include "common.h"
# include "pipex_bonus.h"
# include <termios.h>
# include <readline/readline.h>
# include <readline/history.h>

/* -------------------------------- Typedefs -------------------------------- */

int	g_signal_received;

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