/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwenz <cwenz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 16:35:53 by cwenz             #+#    #+#             */
/*   Updated: 2023/10/15 16:57:08 by cwenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cd(const char *path)
{
	if (chdir(path) != SUCCESS)
	{
		perror("Chdir() failed!\n");
		return (ERROR);
	}
	return (SUCCESS);
}
