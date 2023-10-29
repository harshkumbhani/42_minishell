# include "minishell.h"

static void	execute_pipes(t_minishell *minishell);

void	executor(t_minishell *minishell)
{
	if (!minishell->cmds[1] && is_cmd_builtin(minishell))
		exec_builtins(minishell);
	else
		execute_pipes(minishell);
}

static void	execute_pipes(t_minishell *minishell)
{
	int	i;

	i = 0;
	while (minishell->cmds[i])
	{
		if (minishell->cmds[i + 1])
			execute_child(minishell, i);
		else
			execute_last_child(minishell, i);
		i++;
	}
}
