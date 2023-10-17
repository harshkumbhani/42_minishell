/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwenz <cwenz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 09:10:53 by cwenz             #+#    #+#             */
/*   Updated: 2023/10/17 09:37:47 by cwenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Prints out all the env variables to standard output.
 * 
 * This function iterates over the environment variables provided in `env` and
 * prints each one to standard output.
 * @param env And array of strings where each string is an environment variable.
 * @return EXIT_FAILURE if env is empty or NULL. If all variables were printed
 * it returns EXIT_SUCCESS.
 */
int	env(char **env)
{
	int	i;

	i = 0;
	if (!env || !*env)
		return (EXIT_FAILURE);
	while (env[i])
	{
		printf("%s\n", env[i]);
		i++;
	}
	return (EXIT_SUCCESS);
}
