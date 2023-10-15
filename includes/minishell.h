/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwenz <cwenz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 15:55:14 by cwenz             #+#    #+#             */
/*   Updated: 2023/10/15 17:04:24 by cwenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/* -------------------------------- Includes -------------------------------- */
# include "../libraries/c-library/c_library.h"
# include <signal.h>
# include <stdio.h>
# include <unistd.h>

/* --------------------------------- Macro's -------------------------------- */
# define SUCCESS 0
# define ERROR 1

/* --------------------------------- Signals -------------------------------- */

void    setup_signals();

/* -------------------------------- Built-ins ------------------------------- */

int		cd(const char *path);
int		pwd();

#endif /* MINISHELL_H */