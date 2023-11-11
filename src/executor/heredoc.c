
#include "minishell.h"

static void	execute_heredoc(t_cmd *cmd);

void	handle_heredoc(t_minishell *minishell, int index)
{
	int		pid;

	pipe(minishell->cmd_table[index]->fd);
	pid = fork();
	if (pid == 0)
		execute_heredoc(minishell->cmd_table[index]);
	else
	{
		close(minishell->cmd_table[index]->fd[1]);
		dup2(minishell->cmd_table[index]->fd[0], STDIN_FILENO);
		close(minishell->cmd_table[index]->fd[0]);
		get_exit_status(minishell);
	}
}

static void	execute_heredoc(t_cmd *cmd_table)
{
	char	*str;

	close(cmd_table->fd[0]);
	while (true)
	{
		str = readline("> ");
		if (ft_strcmp(cmd_table->deli, str) == EXIT_SUCCESS)
		{
			free(str);
			break ;
		}
		ft_fprintf(cmd_table->fd[1], "%s\n", str);
		free(str);
	}
	close(cmd_table->fd[1]);
	exit(EXIT_SUCCESS);
}
