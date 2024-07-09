/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   includes.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: harsh <harsh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 12:38:38 by hkumbhan          #+#    #+#             */
/*   Updated: 2024/07/09 15:53:24 by harsh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INCLUDES_H
# define INCLUDES_H

# include "ft_lib.h"
# include <signal.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <stdbool.h>
# include <limits.h>
# include <errno.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <termios.h>
# include <readline/readline.h>
# include <readline/history.h>

# ifdef __linux__
#  include <wait.h>
# endif

/* FILE TYPE macro's*/
# define OPEN 0
# define TRUNC 1
# define APPEND 2

/* RETURN macro's*/
# define SUCCESS 0
# define FAIL	1

/* Error macro's */
# define SYNTAX "minishell: syntax error near unexpected token "
# define QUOTES "minishell: unclosed quotes "
# define MINISHELL "minishell"
# define IDENTIFIER "is not a valid identifier"
# define NOT_FOUND "command not found"
# define NO_DIR "no such file or directory"
# define DIR "is a directory"
# define NO_PERM "permission denied"

#endif
