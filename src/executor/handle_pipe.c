
#include "minishell.h"

// static void	open_infile(t_cmd *cmd);

void	execute_child(t_minishell *minishell, int index)
{
	int	pid;
	int	status;

	pipe(minishell->cmd_table[index]->fd);
	pid = fork();
	// if (pid == -1)
	// 	// TODO: What if it fails?
	if (pid == 0)
	{
		// if (index == 0) // first child
		// 	open_infile(minishell->cmd_table[index]);

		close(minishell->cmd_table[index]->fd[0]); // close read end of pipe
		dup2(minishell->cmd_table[index]->fd[1], STDOUT_FILENO); // duplicate write end of pipe to STDIN_FILENO
		close(minishell->cmd_table[index]->fd[1]); // close write end of pipe
		execute_cmd(minishell->cmd_table[index], minishell->head_env);
	}
	else
	{
		close(minishell->cmd_table[index]->fd[1]); // close write end of pipe
		dup2(minishell->cmd_table[index]->fd[0], STDIN_FILENO); // duplicate write end of pipe to STDIN_FILENO
		close(minishell->cmd_table[index]->fd[0]); // close read end of pipe
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
		close(minishell->cmd_table[index]->fd[1]); // close write end of pipe
		dup2(minishell->cmd_table[index]->fd[0], STDIN_FILENO); // duplicate write end of pipe to STDIN_FILENO
		dup2(minishell->cmd_table[index]->outfile_fd, STDOUT_FILENO); // duplicate to std output
		close(minishell->cmd_table[index]->fd[0]); // close read end of pipe
		execute_cmd(minishell->cmd_table[index], minishell->head_env);
	}
	else
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status)) // get the exit status
			minishell->exit_code = status;
	}
}

// static void	open_infile(t_cmd *cmd)
// {
// 	cmd->infile_fd = open_file(cmd->cmd[1], 0);
// 	if (cmd->infile_fd == -1)
// 	{
// 		/* do something */
// 	}
// 	dup2(cmd->infile_fd, STDIN_FILENO);
// }
