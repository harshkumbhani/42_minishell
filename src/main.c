/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwenz <cwenz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 16:28:03 by cwenz             #+#    #+#             */
/*   Updated: 2023/10/15 17:07:31 by cwenz            ###   ########.fr       */
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
		size_t len = ft_strlen(buffer);
		if (len > 0 && buffer[len - 1] == '\n') {
			buffer[len - 1] = '\0';
		}
		if (ft_strncmp(buffer, "cd ", 3) == SUCCESS)
			cd(buffer + 3);
		else
			return (ERROR);
		// printf("\nRead: %s\n\n", buffer);
	}
	return (0);
}
