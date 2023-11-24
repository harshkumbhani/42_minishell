#include "minishell.h"

static void	execute_heredoc(t_minishell *minishell, int index);
static t_heredoc	*get_last_heredoc(t_heredoc *heredoc);

void	handle_heredoc(t_minishell *minishell, int index)
{
	int		pid;
	t_pids	*pid_node;

	pipe(minishell->fd);
	block_signal();
	pid = fork();
	if (pid == 0)
	{
		setup_heredoc_signals();
		execute_heredoc(minishell, index);
	}
	else
	{
		add_pid(minishell, pid);
		close(minishell->fd[1]);
		dup2(minishell->fd[0], STDIN_FILENO);
		close(minishell->fd[0]);
		pid_node = find_pid(minishell, pid);
		pid_node->has_checked = true;
		get_exit_status(minishell, pid);
		if (*minishell->exit_code == 130)
			g_signal = CTRL_C;
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
