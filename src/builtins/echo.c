/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwenz <cwenz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 09:56:50 by cwenz             #+#    #+#             */
/*   Updated: 2023/11/25 14:52:53 by cwenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_string(char **arg, int start_index, bool new_line);
static bool	has_n_flag(char **args);

/// @brief Executes the echo command with the given `cmd`
///
/// The function prints out the given cmd to standard output. If no args are
/// provided it simply prints a new line. If the -n flag is present it does
/// not print a new line at the end.
/// @param cmd The cmds to print to the standard output
/// @return EXIT_SUCCESS
int	echo(char **cmd)
{
	if (!cmd[1])
	{
		printf("\n");
		return (EXIT_SUCCESS);
	}
	if (has_n_flag(cmd))
		print_string(cmd, 2, false);
	else
		print_string(cmd, 1, true);
	return (EXIT_SUCCESS);
}

/// @brief Prints the given string to standard output.
/// @param arg The strings to print
/// @param start_index The starting index on where to start printing
/// @param new_line A flag to determine if there should be a new line or not.
static void	print_string(char **arg, int start_index, bool new_line)
{
	while (arg[start_index])
	{
		printf("%s", arg[start_index]);
		if (arg[start_index + 1])
			printf(" ");
		start_index++;
	}
	if (new_line)
		printf("\n");
}

/// @brief Checks if the given cmds have a `-n` flag present. 
/// @param args The commands to check.
/// @return TRUE if there is an `-n` flag, otherwise FALSE
static bool	has_n_flag(char **args)
{
	int	i;

	if (args[1][0] != '-')
		return (false);
	i = 1;
	while (args[1][i])
	{
		if (args[1][i] != 'n')
			return (false);
		i++;
	}
	return (true);
}
