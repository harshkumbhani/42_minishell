
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
		str = get_next_line(STDIN_FILENO);
		// fprintf(stderr, "VALUE: %d :: %s. :: %s.\n",ft_strncmp(cmd_table->deli, str, ft_strlen(cmd_table->deli)), cmd_table->deli, str);
		if (ft_strncmp(cmd_table->deli, str, ft_strlen(cmd_table->deli)) == 0)
		{
			free(str);
			break ;
		}
		write(cmd_table->fd[1], str, ft_strlen(str));
		free(str);
	}
	close(cmd_table->fd[1]);
	exit(EXIT_SUCCESS);
}
