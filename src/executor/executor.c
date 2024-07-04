/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: harsh <harsh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 18:30:07 by cwenz             #+#    #+#             */
/*   Updated: 2024/07/04 20:13:15 by harsh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exec_cmd_table(t_minishell *minishell);
static bool	is_simple_builtin(t_minishell *minishell);
static void	wait_for_child_processes(t_minishell *minishell);

/// @brief Determies if the command is a simple builtin or a more complex
/// command. If its a simple builtin, it executes it directly in the parent
/// process. If its a complex command it calls `exec_cmd_table`.
/// @param minishell The minishell struct containing all information about
/// the shell
/// @note See `./src/executor/executor.c` for more details.
void	executor(t_minishell *minishell)
{
	if (is_simple_builtin(minishell))
		exec_builtins(minishell, 0);
	else
		exec_cmd_table(minishell);
}

/// @brief Loops through the given command table stored in the `minishell`
/// struct and executes each command. After executing each command, the
/// parent process then waits for every childs process to finish executing.
/// @param minishell The struct containing all info about the shell and
/// command table.
static void	exec_cmd_table(t_minishell *minishell)
{
	int		i;
	bool	heredoc_flag;

	heredoc_flag = false;
	i = 0;
	minishell->pids = NULL;
	while (minishell->cmd_table[i])
	{
		if (minishell->cmd_table[i]->heredoc)
		{
			heredoc_flag = true;
			reset_fds(minishell);
			handle_heredoc(minishell, i);
		}
		if (*minishell->exit_code == 130 && heredoc_flag)
			return ;
		if (minishell->cmd_table[i + 1])
			execute_cmd_with_pipe(minishell, i);
		else
			execute_final_cmd(minishell, i);
		i++;
	}
	wait_for_child_processes(minishell);
	free_pids(minishell);
}

/// @brief Checks if the given command is a simple builtin or not.
/// The builtins consist of: `cd, export, env, echo, pwd, exit, unset`.
/// @param minishell The struct containing the command table.
/// @return TRUE if its a builting and there are no pipes, heredocs,
/// redirections, otherwise FALSE
static bool	is_simple_builtin(t_minishell *minishell)
{
	if (minishell->cmd_table[0] && minishell->cmd_table[0]->cmd[0]
		&& !minishell->cmd_table[1]
		&& is_cmd_builtin(minishell, 0)
		&& !minishell->cmd_table[0]->files
		&& !minishell->cmd_table[0]->heredoc)
		return (true);
	return (false);
}

/// @brief Loops through all the created pids which are stored in a
/// linked list and waits for each one. The last pid in the
/// linked list will update the exit code.
/// @param minishell The struct containing the linked list of pids.
static void	wait_for_child_processes(t_minishell *minishell)
{
	t_pids	*temp;

	temp = minishell->pids;
	if (!temp)
		return ;
	while (true)
	{
		if (temp && !temp->next)
			break ;
		if (!temp->has_checked)
		{
			waitpid(temp->pid, NULL, 0);
			temp->has_checked = true;
		}
		temp = temp->next;
	}
	if (temp && !temp->has_checked)
		get_exit_status(temp->pid);
}
