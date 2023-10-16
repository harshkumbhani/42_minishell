/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwenz <cwenz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 16:28:03 by cwenz             #+#    #+#             */
/*   Updated: 2023/10/16 08:24:08 by cwenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(void)
{
	setup_signals();
	// Mock shell to check if signal functions actually get called
	pwd();
	while (1)
	{
		char buffer[256];
		char path[256];
		getcwd(path, sizeof(path));
		printf("%s> ", path);
		if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
			break;
		}
		if (ft_strncmp(buffer, "cd ", 3) == SUCCESS)
			cd(buffer + 3);
		else
			return (ERROR);
		// printf("\nRead: %s\n\n", buffer);
	}
	return (0);
}
