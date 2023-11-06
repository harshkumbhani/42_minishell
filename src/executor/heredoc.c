
#include "minishell.h"

void	handle_heredoc(t_minishell *minishell, int index)
{
	char	*str;

	close(minishell->cmd_table[index]->fd[0]);
	while (true)
	{
		str = readline("> ");
		if (ft_strcmp(minishell->cmd_table[index]->cmd[1], str) == EXIT_SUCCESS)
		{
			free(str);
			close(minishell->cmd_table[index]->fd[1]);
			return ;
		}
		// ft_fprintf(minishell->cmd_table[index]->fd[1], "%s\n", str);
		free(str);
	}
}
