
#include "minishell.h"

// TODO: Capture exit code for $?
void	exec_builtins(t_minishell *minishell, int i)
{
	if (ft_strcmp(minishell->cmd_table[i]->cmd[0], "cd") == EXIT_SUCCESS)
		minishell->exit_code = cd(&minishell->head_env, minishell->cmd_table[i]->cmd[1]);
	else if (ft_strcmp(minishell->cmd_table[i]->cmd[0], "pwd") == EXIT_SUCCESS)
		minishell->exit_code = pwd();
	else if (ft_strcmp(minishell->cmd_table[i]->cmd[0], "env") == EXIT_SUCCESS)
		minishell->exit_code = env(minishell->head_env);
	else if (ft_strcmp(minishell->cmd_table[i]->cmd[0], "unset") == EXIT_SUCCESS)
		minishell->exit_code = unset(&minishell->head_env, minishell->cmd_table[0]->cmd[1]);
	else if (ft_strcmp(minishell->cmd_table[i]->cmd[0], "echo") == EXIT_SUCCESS)
		minishell->exit_code = echo();
	else if (ft_strcmp(minishell->cmd_table[i]->cmd[0], "exit") == EXIT_SUCCESS)
		builtin_exit();
	else if (ft_strcmp(minishell->cmd_table[i]->cmd[0], "export") == EXIT_SUCCESS)
		minishell->exit_code = export(&minishell->head_env, minishell->cmd_table[i]->cmd[1]);
}

bool	is_cmd_builtin(t_minishell *minishell, int i)
{
	if (ft_strcmp(minishell->cmd_table[i]->cmd[0], "cd") == EXIT_SUCCESS)
		return (true);
	else if (ft_strcmp(minishell->cmd_table[i]->cmd[0], "pwd") == EXIT_SUCCESS)
		return (true);
	else if (ft_strcmp(minishell->cmd_table[i]->cmd[0], "env") == EXIT_SUCCESS)
		return (true);
	else if (ft_strcmp(minishell->cmd_table[i]->cmd[0], "unset") == EXIT_SUCCESS)
		return (true);
	else if (ft_strcmp(minishell->cmd_table[i]->cmd[0], "echo") == EXIT_SUCCESS)
		return (true);
	else if (ft_strcmp(minishell->cmd_table[i]->cmd[0], "exit") == EXIT_SUCCESS)
		return (true);
	else if (ft_strcmp(minishell->cmd_table[i]->cmd[0], "export") == EXIT_SUCCESS)
		return (true);
	return (false);
}
