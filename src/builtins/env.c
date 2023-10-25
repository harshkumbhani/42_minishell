/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwenz <cwenz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 09:10:53 by cwenz             #+#    #+#             */
/*   Updated: 2023/10/23 13:03:16 by cwenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Prints out all the env variables to standard output.
 * 
 * This function iterates over the environment variables provided in `env` and
 * prints each one to standard output.
 * @param env And array of strings where each string is an environment variable.
 */
void	env(t_env *head)
{
	t_env	*temp;
	
	temp = head;
	if (!temp)
	{
		perror("No env to print!\n");
		return ;
	}
	while (temp)
	{
		printf("%s\n", temp->full_string);
		temp = temp->next;
	}
}
