

#include "minishell.h"

// TODO: Parse struct that holds the last cmds exit status
void	builtin_exit()
{
	// Use the last commands exit status when exiting.
	exit(0);
}
