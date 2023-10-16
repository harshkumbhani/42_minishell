/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwenz <cwenz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 16:28:03 by cwenz             #+#    #+#             */
/*   Updated: 2023/10/16 14:06:18 by cwenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(void)
{
	char tokens[][2] = {
		{"ls", "-la"},
		{"sort", "r"}
	};
	executor(tokens);
	// setup_signals();
	// // Mock shell to check if signal functions actually get called
	// pwd();
	// while (1)
	// {
	// 	char buffer[256];
	// 	char *path;

	// 	path = getcwd(NULL, 0);

	// 	printf("%s> ", path);
	// 	if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
	// 		break;
	// 	}
	// 	if (ft_strncmp(buffer, "cd ", 3) == SUCCESS)
	// 		cd(buffer + 3);
	// 	// printf("\nRead: %s\n\n", buffer);
	// }
	return (0);
}
