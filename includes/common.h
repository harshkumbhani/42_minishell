/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: harsh <harsh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 12:33:16 by cwenz             #+#    #+#             */
/*   Updated: 2023/11/10 10:34:39 by harsh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMON_H
# define COMMON_H

/* -------------------------------- Includes -------------------------------- */
# include "../libraries/myLib/header/library.h"
# include <signal.h>
# include <stdio.h>
# include <unistd.h>
# include <stdbool.h>
# include <limits.h>
# include <errno.h>

// # include <wait.h>

/* --------------------------------- Macro's -------------------------------- */
# define SUCCESS 0
# define ERROR 0

/* -------------------------------- Typedefs -------------------------------- */
typedef enum e_errors
{
	ERR_ARG,
	ERR_INFILE,
	ERR_OUTFILE,
	ERR_CMD1,
	ERR_CMD2,
	ERR_MEMORY,
	ERR_PIPE,
	ERR_FORK,
	ERR_CMD
}	t_errors;

#endif /* COMMON_H */