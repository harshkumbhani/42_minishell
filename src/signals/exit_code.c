/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_code.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwenz <cwenz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 15:08:17 by cwenz             #+#    #+#             */
/*   Updated: 2023/11/25 15:50:16 by cwenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief Stores the exit code.
/// @return The address to the exit code.
int	*get_exit_code(void)
{
	static int	exit_code = 0;

	return (&exit_code);
}

/// @brief Updates the exit code with the given exit code.
/// @param code The code to update the exit code with.
void	set_exit_code(int code)
{
	int	*exit_code;

	exit_code = get_exit_code();
	*exit_code = code;
}
