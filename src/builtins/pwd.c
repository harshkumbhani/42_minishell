/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwenz <cwenz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 17:01:55 by cwenz             #+#    #+#             */
/*   Updated: 2023/10/16 16:07:55 by cwenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

int	pwd()
{
	char	*cwd;

	cwd = getcwd(NULL, sizeof(cwd));
	if (!cwd)
	{
		perror("getcwd() failed!\n");
		return (1);
	}
	printf("%s\n", cwd);
	return (SUCCESS);
}
