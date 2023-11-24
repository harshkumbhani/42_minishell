#include "minishell.h"

static void	exec_cmd_table(t_minishell *minishell);
static bool	is_simple_builtin(t_minishell *minishell);
static void	wait_for_child_processes(t_minishell *minishell);

void	executor(t_minishell *minishell)
{
	if (is_simple_builtin(minishell))
		exec_builtins(minishell, 0);
	else
		exec_cmd_table(minishell);
}

static void	exec_cmd_table(t_minishell *minishell)
{
	int	i;

	i = 0;
	minishell->pids = NULL;
	while (minishell->cmd_table[i])
	{
		if (minishell->cmd_table[i]->heredoc)
		{
			reset_fds(minishell);
			handle_heredoc(minishell, i);
		}
		if (g_signal == CTRL_C)
		{
			g_signal = 0;
			return ;
		}
		if (minishell->cmd_table[i + 1])
			execute_cmd_with_pipe(minishell, i);
		else
			execute_final_cmd(minishell, i);
		i++;
	}
	wait_for_child_processes(minishell);
	free_pids(minishell);
}

static bool	is_simple_builtin(t_minishell *minishell)
{
	if (minishell->cmd_table[0]->cmd[0]
		&& !minishell->cmd_table[1]
		&& is_cmd_builtin(minishell, 0)
		&& !minishell->cmd_table[0]->files
		&& !minishell->cmd_table[0]->heredoc)
		return (true);
	return (false);
}

static void	wait_for_child_processes(t_minishell *minishell)
{
	t_pids	*temp;
	int		i;

	temp = minishell->pids;
	i = 0;
	while (true)
	{
		if (!temp->next)
			break ;
		if (!temp->has_checked)
		{
			waitpid(temp->pid, NULL, 0);
			i++;
			temp->has_checked = true;
		}
		temp = temp->next;
	}
	if (!temp->has_checked)
		get_exit_status(temp->pid);
}
