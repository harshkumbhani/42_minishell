# include "minishell.h"

static void	exec_cmd_table(t_minishell *minishell);

void	executor(t_minishell *minishell)
{
	if (!minishell->cmd_table[1] && is_cmd_builtin(minishell, 0) && !minishell->cmd_table[0]->here_doc)
		exec_builtins(minishell, 0);
	else
		exec_cmd_table(minishell);
}

static void	exec_cmd_table(t_minishell *minishell)
{
	int	i;

	i = 0;
	while (minishell->cmd_table[i])
	{
		if (minishell->cmd_table[i]->here_doc)
			handle_heredoc(minishell, i);
		else if (minishell->cmd_table[i + 1])
			execute_cmd_with_pipe(minishell, i);
		else
			execute_final_cmd(minishell, i);
		i++;
	}
}
