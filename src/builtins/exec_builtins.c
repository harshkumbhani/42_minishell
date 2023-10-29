
#include "minishell.h"

// TODO: Capture exit code for $?
void	exec_builtins(t_minishell *minishell)
{
	if (ft_strcmp(minishell->cmds[0]->cmd[0], "cd") == EXIT_SUCCESS)
		cd(&minishell->head_env);
	else if (ft_strcmp(minishell->cmds[0]->cmd[0], "pwd") == EXIT_SUCCESS)
		pwd();
	else if (ft_strcmp(minishell->cmds[0]->cmd[0], "env") == EXIT_SUCCESS)
		env(minishell->head_env);
	else if (ft_strcmp(minishell->cmds[0]->cmd[0], "unset") == EXIT_SUCCESS)
		unset(&minishell->head_env, "VAR NAME");
	else if (ft_strcmp(minishell->cmds[0]->cmd[0], "echo") == EXIT_SUCCESS)
		echo();
	else if (ft_strcmp(minishell->cmds[0]->cmd[0], "exit") == EXIT_SUCCESS)
		builtin_exit();
	else if (ft_strcmp(minishell->cmds[0]->cmd[0], "export") == EXIT_SUCCESS)
		export(&minishell->head_env, "VAR TO ADD HERE");
}

bool	is_cmd_builtin(t_minishell *minishell)
{
	if (ft_strcmp(minishell->cmds[0]->cmd[0], "cd") == EXIT_SUCCESS)
		return (true);
	else if (ft_strcmp(minishell->cmds[0]->cmd[0], "pwd") == EXIT_SUCCESS)
		return (true);
	else if (ft_strcmp(minishell->cmds[0]->cmd[0], "env") == EXIT_SUCCESS)
		return (true);
	else if (ft_strcmp(minishell->cmds[0]->cmd[0], "unset") == EXIT_SUCCESS)
		return (true);
	else if (ft_strcmp(minishell->cmds[0]->cmd[0], "echo") == EXIT_SUCCESS)
		return (true);
	else if (ft_strcmp(minishell->cmds[0]->cmd[0], "exit") == EXIT_SUCCESS)
		return (true);
	else if (ft_strcmp(minishell->cmds[0]->cmd[0], "export") == EXIT_SUCCESS)
		return (true);
	return (false);
}
