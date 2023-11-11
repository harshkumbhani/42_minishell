
#include "minishell.h"

void	execute_cmd_with_pipe(t_minishell *minishell, int index)
{
	int	pid;

	pipe(minishell->fd);
	pid = fork();
	if (pid == 0)
		execute_child_with_pipe(minishell, index);
	else
	{
		close(minishell->fd[1]);
		dup2(minishell->fd[0], STDIN_FILENO);
		close(minishell->fd[0]);
	}
}

void	execute_final_cmd(t_minishell *minishell, int index)
{
	int	pid;

	pid = fork();
	if (pid == 0)
	{
		dup2(minishell->fd[0], STDIN_FILENO);
		close(minishell->fd[0]);
		if (minishell->cmd_table[index]->infile)
			open_infile(minishell->cmd_table[index]);
		if (minishell->cmd_table[index]->outfile)
			open_outfile(minishell->cmd_table[index]);
		handle_cmd_execution(minishell, index);
	}
	else
	{
		close(minishell->fd[0]);
	}
}
