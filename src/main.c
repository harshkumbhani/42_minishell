/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwenz <cwenz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 16:28:03 by cwenz             #+#    #+#             */
/*   Updated: 2023/10/15 13:31:31 by cwenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(void)
{
	setup_signals();
	// Mock shell to check if signal functions actually get called
	while (1)
	{
		char buffer[256];
		ssize_t bytes_read = read(STDIN_FILENO, buffer, sizeof(buffer) - 1);
		// Crtl-D is an EOF signal? Idk how to handle it yet.
		if (bytes_read <= 0)
		{
			printf("\nEOF Detected! Ctrl-D pressed.\n");
			break;
		}
		buffer[bytes_read] = '\0';
		printf("Read: %s", buffer);
	}
	return (0);
}
