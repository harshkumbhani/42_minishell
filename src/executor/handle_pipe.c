/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwenz <cwenz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 18:30:11 by cwenz             #+#    #+#             */
/*   Updated: 2023/11/26 11:11:47 by cwenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	execute_child_with_pipe(t_minishell *minishell, int index);
static void	handle_cmd_execution(t_minishell *minishell, int index);

/// @brief Executes the given commands for the given index in the command table.
///
/// The function performs a `pipe()` and `fork()` and executes the command in
/// the child process. The parent adds the pid generated from the `fork()`
/// to a linked list and closes file descriptors and `dup2`to standard input.
/// @param minishell The struct that contains the command table and other
/// information related to the shell.
/// @param index The current index in the command table to execute.
void	execute_cmd_with_pipe(t_minishell *minishell, int index)
{
	int	pid;

	if (!minishell->cmd_table[index]->cmd[0]
		&& !minishell->cmd_table[index]->files)
		return ;
	if (pipe(minishell->fd) == -1)
		error_handler(strerror(errno), T_MINI, minishell, NULL);
	block_signal();
	pid = fork();
	if (pid == -1)
		error_handler(strerror(errno), T_MINI, minishell, NULL);
	if (pid == 0)
	{
		setup_child_signals();
		execute_child_with_pipe(minishell, index);
	}
	else
	{
		add_pid(minishell, pid);
		close(minishell->fd[1]);
		dup2(minishell->fd[0], STDIN_FILENO);
		close(minishell->fd[0]);
	}
}

/// @brief Executes the final command in the command table.

/// The function does not `pipe()`, but does still execute it in a child
/// process. The parent closes the standard input and adds the pid
/// to the linked list.
/// @param minishell The struct containing the command table and
/// other information related to the shell.
/// @param index The current index of the command table to execute.
void	execute_final_cmd(t_minishell *minishell, int index)
{
	int	pid;

	if (!minishell->cmd_table[index]->cmd[0]
		&& !minishell->cmd_table[index]->files)
		return ;
	block_signal();
	pid = fork();
	if (pid == -1)
		error_handler(strerror(errno), T_MINI, minishell, NULL);
	if (pid == 0)
	{
		setup_child_signals();
		execute_redir(minishell->cmd_table[index]);
		handle_cmd_execution(minishell, index);
	}
	else
	{
		close(STDIN_FILENO);
		add_pid(minishell, pid);
	}
}

/// @brief Executes a command in a child process with output redirected
/// to a pipe.
///
/// The function is responsible for executing a command in a child process
/// thats part of a pipeline. It closes the read-end, duplicates the
/// write-end to standard output and handles any file redirections.
/// @param minishell The struct containing all shell information.
/// @param index The current index in the command table.
static void	execute_child_with_pipe(t_minishell *minishell, int index)
{
	close(minishell->fd[0]);
	dup2(minishell->fd[1], STDOUT_FILENO);
	close(minishell->fd[1]);
	execute_redir(minishell->cmd_table[index]);
	handle_cmd_execution(minishell, index);
}

/// @brief Determines if the command is a builtin or not.
///
/// If the command is not a builtin it calls `execute_cmd` which passes it
/// to `execve`.
/// @param minishell The struct containing all information related
/// to the shell.
/// @param index The current index in the command table.
/// @note See ./src/executor/command.c for more details. 
static void	handle_cmd_execution(t_minishell *minishell, int index)
{
	if (is_cmd_builtin(minishell, index))
	{
		exec_builtins(minishell, index);
		exit(*minishell->exit_code);
	}
	else
		execute_cmd(minishell->cmd_table[index], minishell->head_env);
}

/// @brief Gets the exit code for the given `pid`. It waits for the
/// process to finish before getting the exit code.
/// @param pid The pid to get the exit code for.
void	get_exit_status(int pid)
{
	int	status;

	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		set_exit_code(WEXITSTATUS(status));
	if (WIFSIGNALED(status))
		set_exit_code(128 + WTERMSIG(status));
}
