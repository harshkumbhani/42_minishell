
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
		close(minishell->cmd_table[index]->fd[0]);
		dup2(minishell->cmd_table[index]->fd[1], STDOUT_FILENO);
		close(minishell->cmd_table[index]->fd[1]);

		execute_cmd(minishell->cmd_table[index], minishell->head_env);
	}
	else
	{
		close(minishell->cmd_table[index]->fd[1]);
		dup2(minishell->cmd_table[index]->fd[0], STDIN_FILENO);
		close(minishell->cmd_table[index]->fd[0]);
		
		get_exit_status(minishell, pid);
	}
}

void	execute_last_child(t_minishell *minishell, int index)
{
	int	pid;

	pid = fork();
	if (pid == 0)
	{
		// open_outfile(minishell->cmd_table[index]);
		close(minishell->cmd_table[index]->fd[1]);
		dup2(minishell->cmd_table[index]->fd[0], STDIN_FILENO);
		close(minishell->cmd_table[index]->fd[0]);

		execute_cmd(minishell->cmd_table[index], minishell->head_env);
	}
	else
		get_exit_status(minishell, pid);
}
