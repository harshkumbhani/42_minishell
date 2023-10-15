/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwenz <cwenz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 17:01:55 by cwenz             #+#    #+#             */
/*   Updated: 2023/10/15 17:04:54 by cwenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

int	pwd()
{
	char cwd[256];

	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		perror("getcwd() failed!\n");
		return (ERROR);
	}
	printf("%s\n", cwd);
	return (SUCCESS);
}
