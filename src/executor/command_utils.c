/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwenz <cwenz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 16:15:35 by cwenz             #+#    #+#             */
/*   Updated: 2023/11/25 10:08:19 by cwenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief Checks what error message to display and what error code to exit
///	with. It checks if the path is a directory, if its an executable, or if
/// the command is found.
/// @param path The filesystem path to the file or command to be executed.
/// @return An integer representing the exit code. Returns 126 for a directory
/// or if no permission and 127 if the command is not found.
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
