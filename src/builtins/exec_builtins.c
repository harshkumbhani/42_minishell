

#include "minishell.h"

// TODO: Pass in struct that will hold the cmds and update function parameters!!!
// TODO: Capture exit code for $?
void	exec_builtins()
{
	char *cmd = NULL; // change this, this is just placeholder for now
	t_env *head = NULL; // change this, this is just placeholder for now
	if (ft_strcmp(cmd, "cd") == EXIT_SUCCESS)
		cd(&head);
	else if (ft_strcmp(cmd, "pwd") == EXIT_SUCCESS)
		pwd();
	else if (ft_strcmp(cmd, "env") == EXIT_SUCCESS)
		env(head);
	else if (ft_strcmp(cmd, "unset") == EXIT_SUCCESS)
		unset(&head, "VAR NAME");
	else if (ft_strcmp(cmd, "echo") == EXIT_SUCCESS)
		echo();
	else if (ft_strcmp(cmd, "exit") == EXIT_SUCCESS)
		builtin_exit();
	else if (ft_strcmp(cmd, "export") == EXIT_SUCCESS)
		export(&head, "VAR TO ADD HERE");
}
