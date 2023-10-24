/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwenz <cwenz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 09:56:50 by cwenz             #+#    #+#             */
/*   Updated: 2023/10/24 15:02:53 by cwenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_string(char **arg, int start_index, bool new_line);
static bool	has_n_flag(char **args);

// TODO: Pass down command table to it and store exit code:
void	echo(void)
{
	// for testing:
	char	*args[] = {"echo", "b-nnnn", "-n", "-n" , "-n ", "Hello world", NULL};
	// char	*args[] = {"echo", NULL};
	// char	*args[] = {"echo", "Hello world", "-n", NULL};
	// char	*args[] = {"echo", "Helloworld", "something", NULL};
	if (!args[1])
	{
		printf("\n");
		return ;
	}
	if (has_n_flag(args))
		print_string(args, 2, false);
	else
		print_string(args, 1, true);
}

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
