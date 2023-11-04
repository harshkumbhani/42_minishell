
#include "minishell.h"

static void	handle_heredoc(t_minishell *minishell, int index);

void	get_exit_status(t_minishell *minishell, int	pid)
{
	int	status;

	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		minishell->exit_code = WEXITSTATUS(status);
	// convention in unix operating systems to return the exit status as 128 + status when process is terminated by a signal
	if (WIFSIGNALED(status))
		minishell->exit_code = 128 + WTERMSIG(status);
}

void	execute_child_with_pipe(t_minishell *minishell, int index)
{
	if (index > 0)
	{
		dup2(minishell->cmd_table[index - 1]->fd[0], STDIN_FILENO);
		close(minishell->cmd_table[index - 1]->fd[0]);
	}
	close(minishell->cmd_table[index]->fd[0]);
	dup2(minishell->cmd_table[index]->fd[1], STDOUT_FILENO);
	close(minishell->cmd_table[index]->fd[1]);
	handle_cmd_execution(minishell, index);
}

void	handle_cmd_execution(t_minishell *minishell, int index)
{
	if (is_cmd_builtin(minishell, index))
	{
		exec_builtins(minishell, index);
		exit(minishell->exit_code);
	}
	else if (minishell->cmd_table[index]->here_doc)
	{
		handle_heredoc(minishell, index);
		exit(EXIT_SUCCESS);
	}
	else
		execute_cmd(minishell->cmd_table[index], minishell->head_env);
}

static void	handle_heredoc(t_minishell *minishell, int index)
{
	char	*str;

	while (true)
	{
		ft_fprintf(STDERR_FILENO, "> ");
		str = get_next_line(STDIN_FILENO);
		if (!str)
			return ;
		if (ft_strcmp(minishell->cmd_table[index]->deli, str) == EXIT_SUCCESS)
		{
			free(str);
			return ;
		}
		ft_fprintf(minishell->cmd_table[index]->fd[1], "%s", str);
		free(str);
	}
}
