
#include "minishell.h"

void	execute_child(t_minishell *minishell, int index)
{
	int	pid;

	pipe(minishell->cmd_table[index]->fd);
	pid = fork();
	if (pid == 0)
	{
		if (minishell->cmd_table[index]->infile)
			open_infile(minishell->cmd_table[index]);
		if (index > 0)
		{
			dup2(minishell->cmd_table[index - 1]->fd[0], STDIN_FILENO);
			close(minishell->cmd_table[index - 1]->fd[0]);
		}
		close(minishell->cmd_table[index]->fd[0]);
		dup2(minishell->cmd_table[index]->fd[1], STDOUT_FILENO);
		close(minishell->cmd_table[index]->fd[1]);
		if (is_cmd_builtin(minishell, index))
		{
			exec_builtins(minishell, index);
			exit(minishell->exit_code);
		}
		else
			execute_cmd(minishell->cmd_table[index], minishell->head_env);
	}
	else
	{
		close(minishell->cmd_table[index]->fd[1]);
		if (index > 0)
			close(minishell->cmd_table[index - 1]->fd[0]);
		get_exit_status(minishell, pid);
	}
}

void	execute_last_child(t_minishell *minishell, int index)
{
	int	pid;

	pid = fork();
	if (pid == 0)
	{
		if (index > 0)
		{
			dup2(minishell->cmd_table[index - 1]->fd[0], STDIN_FILENO);
			close(minishell->cmd_table[index - 1]->fd[0]);
		}
		if (is_cmd_builtin(minishell, index))
		{
			exec_builtins(minishell, index);
			exit(minishell->exit_code);
		}
		else
			execute_cmd(minishell->cmd_table[index], minishell->head_env);
	}
	else
	{
		if (index > 0)
			close(minishell->cmd_table[index - 1]->fd[0]);
		get_exit_status(minishell, pid);
	}
}
