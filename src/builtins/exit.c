/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwenz <cwenz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 16:39:13 by cwenz             #+#    #+#             */
/*   Updated: 2023/11/12 16:39:16 by cwenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// TODO: Parse struct that holds the last cmds exit status
void	builtin_exit(t_minishell *minishell)
{
	//1. free stuff:
		// free_everything()
	ft_fprintf(STDOUT_FILENO, "exit\n");
	exit(minishell->exit_code);
}
