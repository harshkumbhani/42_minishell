# include "minishell.h"

static void	execute_pipes(t_minishell *minishell);

void	executor(t_minishell *minishell)
{
	if (!minishell->cmds[1] && is_cmd_builtin(minishell))
		exec_builtins(minishell);
	else
		execute_pipes(minishell);
}

static void	execute_pipes(t_minishell *minishell)
{
	int	i;

	i = 0;
	while (minishell->cmds[i])
	{
		if (minishell->cmds[i + 1])
			execute_child(minishell, i);
		else
			execute_last_child(minishell, i);
		i++;
	}
		/*
		pipe(minishell->cmds[i]->fd);
		pid = fork();

		if (pid == -1)
			exit(EXIT_FAILURE);
		if (pid == 0)
		{
			close(minishell->cmds[i]->fd[0]);
			dup2(minishell->cmds[i]->infile_fd, STDIN_FILENO);
			dup2(minishell->cmds[i]->fd[1], STDOUT_FILENO);
			close(minishell->cmds[i]->fd[1]);
			execute_cmd(minishell->cmds[i], minishell->head_env);
		}
		else
		{
			close(minishell->cmds[i]->fd[1]);
			if (i > 0)
				close(minishell->cmds[i]->infile_fd);
			minishell->cmds[i]->infile_fd = minishell->cmds[i]->fd[0];
			close(minishell->cmds[i]->fd[0]);
			waitpid(pid, &status, 0);
			if (WIFEXITED(status))
				minishell->exit_code = status;
		}
		*/
}
