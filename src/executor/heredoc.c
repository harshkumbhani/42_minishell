
#include "minishell.h"

void	handle_heredoc(t_minishell *minishell, int index)
{
	char	*str;

	while (true)
	{
		ft_fprintf(STDIN_FILENO, "> ");
		str = get_next_line(STDIN_FILENO);
		if (!str)
			return ;
		printf("Comparing: %s. :: %s.\n\n", minishell->cmd_table[index]->deli, str);
		if (ft_strcmp(minishell->cmd_table[index]->deli, str) == EXIT_SUCCESS)
		{
			free(str);
			return ;
		}
		ft_fprintf(minishell->cmd_table[index]->fd[1], "%s", str);
		free(str);
	}
}
