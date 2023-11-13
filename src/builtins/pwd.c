/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwenz <cwenz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 17:01:55 by cwenz             #+#    #+#             */
/*   Updated: 2023/11/12 16:59:09 by cwenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		ft_fprintf(STDERR_FILENO, "minishell: pwd: %s\n", strerror(errno));
		return (EXIT_FAILURE);
	}
	printf("%s\n", cwd);
	free(cwd);
	return (EXIT_SUCCESS);
}
