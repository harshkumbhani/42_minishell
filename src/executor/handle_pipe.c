
#include "minishell.h"

void	execute_cmd_with_pipe(t_minishell *minishell, int index)
{
	int	pid;

	pipe(minishell->cmd_table[index]->fd);
	pid = fork();
	if (pid == 0)
		execute_child_with_pipe(minishell, index);
	else
	{
		close(minishell->cmd_table[index]->fd[1]);
		if (index > 0)
			close(minishell->cmd_table[index - 1]->fd[0]);
		get_exit_status(minishell, pid);
	}
}

void	execute_final_cmd(t_minishell *minishell, int index)
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
		handle_cmd_execution(minishell, index);
	}
	else
	{
		if (index > 0)
			close(minishell->cmd_table[index - 1]->fd[0]);
		get_exit_status(minishell, pid);
	}
}
