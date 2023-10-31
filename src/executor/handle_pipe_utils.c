
#include "minishell.h"

void	get_exit_status(t_minishell *minishell, int	pid)
{
	int	status;

	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		minishell->exit_code = WEXITSTATUS(status);
}
