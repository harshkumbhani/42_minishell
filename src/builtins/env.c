/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwenz <cwenz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 09:10:53 by cwenz             #+#    #+#             */
/*   Updated: 2023/11/12 15:05:57 by cwenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Prints out all the env variables to standard output.
 * 
 * This function iterates over the environment variables provided in `env` and
 * prints each one to standard output. If the format_as_export_command is true,
 * the env variables are printed in the format for export 
 * (e.g. declare -x VAR=Hello world). Otherwise they are printed in standard
 * format (e.g. VAR=Hello world).
 * @param env And array of strings where each string is an environment variable.
 * @param format_as_export_command Determines the format of the output, if true
 * it prints it out as export format, otherwise env variables are printed in
 * plain format
 * @return EXIT_SUCESS after printing all the nodes.
 */
int	env(t_env *head)
{
	t_env	*temp;

	temp = head;
	while (temp)
	{
		ft_fprintf(STDOUT_FILENO, "%s\n", temp->full_string);
		temp = temp->next;
	}
	return (EXIT_SUCCESS);
}
