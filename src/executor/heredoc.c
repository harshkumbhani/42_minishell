#include "minishell.h"

static void	execute_heredoc(t_minishell *minishell, int index);

void	handle_heredoc(t_minishell *minishell, int index)
{
	int		pid;

	pipe(minishell->fd);
	pid = fork();
	if (pid == 0)
	{
		
		execute_heredoc(minishell, index);
	}
	else
	{
		close(minishell->fd[1]);
		dup2(minishell->fd[0], STDIN_FILENO);
		close(minishell->fd[0]);
		get_exit_status(minishell);
	}
}

static void	execute_heredoc(t_minishell *minishell, int index)
{
	char	*str;

	close(minishell->fd[0]);
	while (true)
	{
		str = readline("> ");
		if (!str)
			break ;
		if (ft_strncmp(minishell->cmd_table[index]->deli,
				str, ft_strlen(minishell->cmd_table[index]->deli)) == 0)
		{
			free(str);
			break ;
		}
		write(minishell->fd[1], str, ft_strlen(str));
		write(minishell->fd[1], "\n", 1);
		free(str);
	}
	close(minishell->fd[1]);
	exit(EXIT_SUCCESS);
}
