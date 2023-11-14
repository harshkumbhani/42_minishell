#include "minishell.h"

void	copy_env_variables(t_env **head, char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		process_string(head, envp[i]);
		i++;
	}
}
