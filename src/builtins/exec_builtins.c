/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwenz <cwenz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 16:38:01 by cwenz             #+#    #+#             */
/*   Updated: 2023/11/28 11:11:12 by cwenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief Executes the current builtin.
/// @param minishell The struct holding all shell data
/// @param i The current index of the command table
void	exec_builtins(t_minishell *minishell, int i)
{
	int	code;

	code = 0;
	if (ft_strcmp(minishell->cmd_table[i]->cmd[0], "cd") == 0)
		code = cd(&minishell->head_env,
				minishell->cmd_table[i]->cmd[1]);
	else if (ft_strcmp(minishell->cmd_table[i]->cmd[0], "pwd") == 0)
		code = pwd();
	else if (ft_strcmp(minishell->cmd_table[i]->cmd[0], "env") == 0)
		code = env(minishell->head_env);
	else if (ft_strcmp(minishell->cmd_table[i]->cmd[0], "unset") == 0)
		code = unset(&minishell->head_env,
				minishell->cmd_table[0]->cmd);
	else if (ft_strcmp(minishell->cmd_table[i]->cmd[0], "echo") == 0)
		code = echo(minishell->cmd_table[i]->cmd);
	else if (ft_strcmp(minishell->cmd_table[i]->cmd[0], "exit") == 0)
		builtin_exit(minishell, i);
	else if (ft_strcmp(minishell->cmd_table[i]->cmd[0], "export") == 0)
		code = export(&minishell->head_env,
				minishell->cmd_table[i]->cmd + 1);
	set_exit_code(code);
}

/// @brief Checks to see if the given command is a builtin
/// @param minishell The struct holding all shell data
/// @param i The current index of the command table
/// @return TRUE if its a builtin, otherwise FALSE.
bool	is_cmd_builtin(t_minishell *minishell, int i)
{
	if (minishell->cmd_table == NULL)
		return (false);
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
