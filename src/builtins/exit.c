

#include "minishell.h"

// TODO: Parse struct that holds the last cmds exit status
void	builtin_exit(t_minishell *minishell)
{
	//1. free stuff:
		// free_everything()
	exit(minishell->exit_code);
}
