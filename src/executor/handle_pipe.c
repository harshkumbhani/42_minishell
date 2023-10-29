
#include "minishell.h"

void	execute_child(t_minishell *minishell, int index)
{
	int	pid;
	int	status;

	pipe(minishell->cmds[index]->fd);
	pid = fork();
	// if (pid == -1)
	// 	// TODO: What if it fails?
	if (pid == 0)
	{
		if (index == 0) // first child
			// open_infile(minishell->cmds[index]);

		close(minishell->cmds[index]->fd[0]); // close read end of pipe
		dup2(minishell->cmds[index]->fd[1], STDOUT_FILENO); // duplicate write end of pipe to STDIN_FILENO
		close(minishell->cmds[index]->fd[1]); // close write end of pipe
		execute_cmd(minishell->cmds[index], minishell->head_env);
	}
	else
	{
		close(minishell->cmds[index]->fd[1]); // close write end of pipe
		dup2(minishell->cmds[index]->fd[0], STDIN_FILENO); // duplicate write end of pipe to STDIN_FILENO
		close(minishell->cmds[index]->fd[0]); // close read end of pipe
		waitpid(pid, &status, 0);
		if (WIFEXITED(status)) // get the exit status
			minishell->exit_code = status;
	}
}

void	execute_last_child(t_minishell *minishell, int index)
{
	int	pid;
	int	status;

	// since last child, no need to pipe
	pid = fork();
	// if (pid == -1)
	// 	// TODO: ???
	if (pid == 0)
	{
		close(minishell->cmds[index]->fd[1]); // close write end of pipe
		dup2(minishell->cmds[index]->fd[0], STDIN_FILENO); // duplicate write end of pipe to STDIN_FILENO
		dup2(minishell->cmds[index]->outfile_fd, STDOUT_FILENO); // duplicate to std output
		close(minishell->cmds[index]->fd[0]); // close read end of pipe

		execute_cmd(minishell->cmds[index], minishell->head_env);
	}
	else
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status)) // get the exit status
			minishell->exit_code = status;
	}
}
