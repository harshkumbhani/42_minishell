# include "minishell.h"

static void	execute_pipes(t_minishell *minishell);

void	executor(t_minishell *minishell)
{
	if (!minishell->cmd_table[1] && is_cmd_builtin(minishell, 0))
		exec_builtins(minishell, 0);
	else
		execute_pipes(minishell);
}

static void	execute_pipes(t_minishell *minishell)
{
	int	i;

	i = 0;
	while (minishell->cmd_table[i])
	{
		if (minishell->cmd_table[i + 1])
			execute_child(minishell, i);
		else
			execute_last_child(minishell, i);
		i++;
	}
}
