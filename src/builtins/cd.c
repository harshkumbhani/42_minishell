/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwenz <cwenz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 16:35:53 by cwenz             #+#    #+#             */
/*   Updated: 2023/10/16 12:38:09 by cwenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cd(char *path)
{
	int	len;
	
	if (!path)
		return (1);
	len = ft_strlen(path);
	if (len > 0 && path[len - 1] == '\n')
		path[len - 1] = '\0';
	if (chdir(path) != SUCCESS)
	{
		perror("Chdir() failed!\n");
		return (1);
	}
	return (SUCCESS);
}
