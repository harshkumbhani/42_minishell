/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   includes.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkumbhan <hkumbhan@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 12:38:38 by hkumbhan          #+#    #+#             */
/*   Updated: 2023/11/28 11:02:48 by hkumbhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INCLUDES_H
# define INCLUDES_H

# include "../libraries/myLib/header/library.h"
# include <signal.h>
# include <stdio.h>
# include <unistd.h>
# include <stdbool.h>
# include <limits.h>
# include <errno.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <termios.h>
# include <readline/readline.h>
# include <readline/history.h>
//# include <wait.h>

/* FILE TYPE macro's*/
# define OPEN 0
# define TRUNC 1
# define APPEND 2

/* RETURN macro's*/
# define SUCCESS 0
# define FAIL	1

/* Error macro's */
# define SYNTAX "minishell: syntax error near unexpected token"
# define QUOTES "minishell: unclosed quotes"
# define MINISHELL "minishell"
# define IDENTIFIER "is not a valid identifier"
# define NOT_FOUND "command not found"
# define NO_DIR "no such file or directory"
# define DIR "is a directory"
# define NO_PERM "permission denied"

#endif