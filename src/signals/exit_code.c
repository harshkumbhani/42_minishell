/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_code.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwenz <cwenz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 15:08:17 by cwenz             #+#    #+#             */
/*   Updated: 2023/11/24 17:06:22 by cwenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	*get_exit_code()
{
	static int	exit_code = 0;

	return (&exit_code);
}
void	set_exit_code(int code)
{
	int	*exit_code;

	exit_code = get_exit_code();
	*exit_code = code;
}
