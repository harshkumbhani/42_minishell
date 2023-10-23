

#include "minishell.h"

// TODO: Pass in struct that will hold the cmds and update function parameters!!!
void	exec_builtins()
{
	char *cmd = NULL; // change this, this is just placeholder for now
	char *path = NULL; // change this, this is just placeholder for now
	t_env *head = NULL; // change this, this is just placeholder for now
	if (ft_strncmp(cmd, "cd ", 3) == EXIT_SUCCESS)
		cd(path);
	else if (ft_strncmp(cmd, "pwd", 3) == EXIT_SUCCESS)
		pwd();
	else if (ft_strncmp(cmd, "env", 3) == EXIT_SUCCESS)
		env(head);
	else if (ft_strncmp(cmd, "unset", 5) == EXIT_SUCCESS)
		unset(&head, "VAR NAME");
	else if (ft_strncmp(cmd, "echo", 4) == EXIT_SUCCESS)
		echo();
	else if (ft_strncmp(cmd, "exit", 4) == EXIT_SUCCESS)
		builtin_exit();
	else if (strncmp(cmd, "export", 6) == EXIT_SUCCESS)
		head = add_env_row(head, "VAR TO ADD HERE");
}
