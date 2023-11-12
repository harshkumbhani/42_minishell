
#include "minishell.h"

void	get_exit_status(t_minishell *minishell)
{
	int	status;

	waitpid(0, &status, 0);
	if (WIFEXITED(status))
		minishell->exit_code = WEXITSTATUS(status);
	// convention in unix operating systems to return the exit status as 128 + status when process is terminated by a signal
	if (WIFSIGNALED(status))
		minishell->exit_code = 128 + WTERMSIG(status);
}

void	execute_child_with_pipe(t_minishell *minishell, int index)
{
	close(minishell->fd[0]);
	if (minishell->cmd_table[index]->infile)
		open_infile(minishell->cmd_table[index]);
	else
		dup2(minishell->fd[0], STDIN_FILENO);
	dup2(minishell->fd[1], STDOUT_FILENO);
	close(minishell->fd[1]);

	if (minishell->cmd_table[index]->outfile)
		open_outfile(minishell->cmd_table[index]);
	handle_cmd_execution(minishell, index);
}

void	handle_cmd_execution(t_minishell *minishell, int index)
{
	if (is_cmd_builtin(minishell, index))
	{
		exec_builtins(minishell, index);
		exit(minishell->exit_code);
	}
	else
		execute_cmd(minishell->cmd_table[index], minishell->head_env);
}
