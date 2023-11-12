/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwenz <cwenz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 16:39:13 by cwenz             #+#    #+#             */
/*   Updated: 2023/11/12 19:26:07 by cwenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin_exit(t_minishell *minishell)
{
	if (!minishell->cmd_table[1])
	{
		free_env_linked_list(minishell->head_env);
		free_cmd_table(minishell->cmd_table);
		ft_fprintf(STDOUT_FILENO, "exit\n");
		exit(minishell->exit_code);
	}
}
