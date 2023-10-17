/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwenz <cwenz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 16:35:53 by cwenz             #+#    #+#             */
/*   Updated: 2023/10/17 09:34:27 by cwenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Changes the current working directory.
 * 
 * If no path is provided, it will attempt to change the directory to the
 * specified by the HOME env variable.
 * If a path is given, it will attempt to change it to that directory.
 * 
 * @param path The path to change the directory, if its NULL or empty, it
 * changes to the directory specified in HOME env variable
 * @return EXIT_SUCCESS if the directory was changed, else EXIT_FAILURE.
 */
int	cd(char *path)
{
	int	len;
	
	if (!path || !*path)
	{
		path = getenv("HOME");
		if (!path)
			return (EXIT_FAILURE);
	}
	len = ft_strlen(path);
	if (len > 0 && path[len - 1] == '\n')
		path[len - 1] = '\0';
	if (chdir(path) != EXIT_SUCCESS)
	{
		perror("Chdir() failed!\n");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
