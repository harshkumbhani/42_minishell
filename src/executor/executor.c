#include "minishell.h"

static void	exec_cmd_table(t_minishell *minishell);
static bool	is_simple_builtin(t_minishell *minishell);
static void	wait_for_child_processes(t_minishell *minishell);
static int	find_mode(t_minishell *minishell, int index);

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
	int		mode;
	int		i;

	temp = minishell->pids;
	i = 0;
	while (temp)
	{
		mode = find_mode(minishell, i);
		get_exit_status(minishell, temp->pid, mode);
		i++;
		temp = temp->next;
	}
}

static int	find_mode(t_minishell *minishell, int index)
{
	char	**cmds;
	int		i;

	i = 0;
	cmds = minishell->cmd_table[index]->cmd;
	if (!cmds)
		return (0);
	while (cmds[i])
	{
		if (ft_strcmp(cmds[i], "/dev/random") == 0 || ft_strcmp(cmds[i], "/dev/urandom") == 0)
			return (1);
		i++;
	}
	return (0);
}
