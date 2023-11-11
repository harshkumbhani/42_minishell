/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwenz <cwenz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 09:10:53 by cwenz             #+#    #+#             */
/*   Updated: 2023/11/02 12:58:45 by cwenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Prints out all the env variables to standard output.
 * 
 * This function iterates over the environment variables provided in `env` and
 * prints each one to standard output.
 * @param env And array of strings where each string is an environment variable.
 * @return EXIT_SUCESS after printing all the nodes.
 */
int	env(t_env *head)
{
	t_env	*temp;
	
	temp = head;
	while (temp)
	{
		ft_printf("%s\n", temp->full_string);
		temp = temp->next;
	}
	return (EXIT_SUCCESS);
}
