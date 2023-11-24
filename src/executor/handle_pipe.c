#include "minishell.h"

static void	execute_child_with_pipe(t_minishell *minishell, int index);
static void	handle_cmd_execution(t_minishell *minishell, int index);

void	execute_cmd_with_pipe(t_minishell *minishell, int index)
{
	int	pid;

	pipe(minishell->fd);
	block_signal();
	pid = fork();
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

void	execute_final_cmd(t_minishell *minishell, int index)
{
	int	pid;

	if (minishell->cmd_table[index]->cmd[0] == NULL)
		return ;
	block_signal();
	pid = fork();
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

static void	execute_child_with_pipe(t_minishell *minishell, int index)
{
	close(minishell->fd[0]);
	dup2(minishell->fd[1], STDOUT_FILENO);
	close(minishell->fd[1]);
	execute_redir(minishell->cmd_table[index]);
	handle_cmd_execution(minishell, index);
}

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

void	get_exit_status(t_minishell *minishell, int pid)
{
	int	status;

	(void)minishell;
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		set_exit_code(WEXITSTATUS(status));
	if (WIFSIGNALED(status))
		set_exit_code(128 + WTERMSIG(status));
}
