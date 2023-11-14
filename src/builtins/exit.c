/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwenz <cwenz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 16:39:13 by cwenz             #+#    #+#             */
/*   Updated: 2023/11/13 22:49:40 by cwenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_exit_code_digit(char *exit_code);
static void	free_minishell_and_exit(t_minishell *minishell, int exit_code);

void	builtin_exit(t_minishell *minishell, int index)
{
	int	exit_code;
	int	cmd_num;
	
	cmd_num = 1;
	exit_code = minishell->exit_code;
	while (minishell->cmd_table[index]->cmd[cmd_num])
		cmd_num++;
	if (!minishell->cmd_table[1])
		ft_fprintf(STDOUT_FILENO, "exit\n");
	if (minishell->cmd_table[index]->cmd[1])
	{
		if (!is_exit_code_digit(minishell->cmd_table[index]->cmd[1]))
		{
			error_msg("exit", minishell->cmd_table[index]->cmd[1], "numeric argument required");
			free_minishell_and_exit(minishell, 1);
		}
		exit_code = ft_atoi(minishell->cmd_table[index]->cmd[1]);
	}
	if (cmd_num > 2)
	{
		error_msg("exit", NULL, "too many arguments");
		return ;
	}
	free_minishell_and_exit(minishell, exit_code);
}

static bool	is_exit_code_digit(char *exit_code)
{
	int	i;
	
	i = 0;
	while (exit_code[i])
	{
		if (ft_isdigit(exit_code[i]) == 0)
			return (false);
		i++;
	}
	return (true);
}

static void	free_minishell_and_exit(t_minishell *minishell, int exit_code)
{
	free_env_linked_list(minishell->head_env);
	free_cmd_table(minishell->cmd_table);
	exit(exit_code);
}