
#include "minishell.h"

void	get_exit_status(t_minishell *minishell, int	pid)
{
	int	status;

	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		minishell->exit_code = WEXITSTATUS(status);
	// convention in unix operating systems to return the exit status as 128 + status when process is terminated by a signal
	if (WIFSIGNALED(status))
		minishell->exit_code = 128 + WTERMSIG(status);
}
