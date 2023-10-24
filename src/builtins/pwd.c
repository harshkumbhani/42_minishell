/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwenz <cwenz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 17:01:55 by cwenz             #+#    #+#             */
/*   Updated: 2023/10/24 15:01:17 by cwenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

/**
 * @brief Prints out the current working directory to standard output.
 * @return EXIT_FAILURE if it cannot aquire the `cwd`, else EXIT_SUCCESS.
 */
int	pwd(void)
{
	char	*cwd;

	cwd = getcwd(NULL, sizeof(cwd));
	if (!cwd)
	{
		perror("getcwd() failed!\n");
		return (EXIT_FAILURE);
	}
	printf("%s\n", cwd);
	free(cwd);
	return (EXIT_SUCCESS);
}
