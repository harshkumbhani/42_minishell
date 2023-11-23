#include "minishell.h"

static void	execute_heredoc(t_minishell *minishell, int index);
static t_heredoc	*get_last_heredoc(t_heredoc *heredoc);

void	handle_heredoc(t_minishell *minishell, int index)
{
	int		pid;
	// int		status;

	pipe(minishell->fd);
	block_signal();
	pid = fork();
	if (pid == 0)
	{
		setup_child_signals();
		execute_heredoc(minishell, index);
	}
	else
	{
		close(minishell->fd[1]);
		dup2(minishell->fd[0], STDIN_FILENO);
		close(minishell->fd[0]);
		// get_exit_status(minishell);
		waitpid(pid, NULL, 0);
		// if (WIFEXITED(status))
		// 	minishell->exit_code = WEXITSTATUS(status);
		// if (WIFSIGNALED(status))
		// 	minishell->exit_code = 128 + WTERMSIG(status);
	}
}

static void	execute_heredoc(t_minishell *minishell, int index)
{
	char		*str;
	t_heredoc	*temp;
	t_heredoc	*last_heredoc;

	temp = minishell->cmd_table[index]->heredoc;
	last_heredoc = get_last_heredoc(temp);
	close(minishell->fd[0]);
	while (temp)
	{
		while (true)
		{
			str = readline("> ");
			if (!str)
				break ;
			if (ft_strncmp(temp->str,
					str, ft_strlen(temp->str)) == 0)
			{
				free(str);
				break ;
			}
			if (last_heredoc == temp)
			{
				if (temp->expand)
					str = expander(str, ft_strlen(str), minishell);
				write(minishell->fd[1], str, ft_strlen(str));
				write(minishell->fd[1], "\n", 1);
			}
			free(str);
		}
		temp = temp->next;
	}
	close(minishell->fd[1]);
	exit(0);
}


static t_heredoc	*get_last_heredoc(t_heredoc *heredoc)
{
	while (heredoc->next)
		heredoc = heredoc->next;
	return (heredoc);
}
