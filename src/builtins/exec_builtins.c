/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwenz <cwenz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 16:38:01 by cwenz             #+#    #+#             */
/*   Updated: 2023/11/14 13:49:13 by cwenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_builtins(t_minishell *minishell, int i)
{
	if (ft_strcmp(minishell->cmd_table[i]->cmd[0], "cd") == 0)
		minishell->exit_code = cd(&minishell->head_env,
				minishell->cmd_table[i]->cmd[1]);
	else if (ft_strcmp(minishell->cmd_table[i]->cmd[0], "pwd") == 0)
		minishell->exit_code = pwd();
	else if (ft_strcmp(minishell->cmd_table[i]->cmd[0], "env") == 0)
		minishell->exit_code = env(minishell->head_env);
	else if (ft_strcmp(minishell->cmd_table[i]->cmd[0], "unset") == 0)
		minishell->exit_code = unset(&minishell->head_env,
				minishell->cmd_table[0]->cmd);
	else if (ft_strcmp(minishell->cmd_table[i]->cmd[0], "echo") == 0)
		minishell->exit_code = echo(minishell->cmd_table[i]->cmd);
	else if (ft_strcmp(minishell->cmd_table[i]->cmd[0], "exit") == 0)
		builtin_exit(minishell, i);
	else if (ft_strcmp(minishell->cmd_table[i]->cmd[0], "export") == 0)
		minishell->exit_code = export(&minishell->head_env,
				minishell->cmd_table[i]->cmd + 1);
}

bool	is_cmd_builtin(t_minishell *minishell, int i)
{
	if (ft_strcmp(minishell->cmd_table[i]->cmd[0], "cd") == 0)
		return (true);
	else if (ft_strcmp(minishell->cmd_table[i]->cmd[0], "pwd") == 0)
		return (true);
	else if (ft_strcmp(minishell->cmd_table[i]->cmd[0], "env") == 0)
		return (true);
	else if (ft_strcmp(minishell->cmd_table[i]->cmd[0], "unset") == 0)
		return (true);
	else if (ft_strcmp(minishell->cmd_table[i]->cmd[0], "echo") == 0)
		return (true);
	else if (ft_strcmp(minishell->cmd_table[i]->cmd[0], "exit") == 0)
		return (true);
	else if (ft_strcmp(minishell->cmd_table[i]->cmd[0], "export") == 0)
		return (true);
	return (false);
}
