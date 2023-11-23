/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwenz <cwenz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 16:15:35 by cwenz             #+#    #+#             */
/*   Updated: 2023/11/22 13:15:29 by cwenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_file_execution_errors(char *path)
{
	struct stat	buf;
	int			exit_code;

	exit_code = 1;
	if (stat(path, &buf) == 0)
	{
		if (S_ISDIR(buf.st_mode))
		{
			error_msg(path, NULL, DIR);
			exit_code = 126;
		}
		else if (ft_strchr(path, '/') && access(path, X_OK) == -1)
		{
			error_msg(path, NULL, NO_PERM);
			exit_code = 126;
		}
		else
		{
			error_msg(path, NULL, NOT_FOUND);
			exit_code = 127;
		}
	}
	return (exit_code);
}
