
#include "minishell.h"

static void	execute_heredoc(t_cmd *cmd);
static int	has_cmd(t_cmd *cmd_table);
static void	execute_heredoc_cmd(t_minishell *minishell, int index);
static char	**assign_new_cmd_without_heredoc(char **cmd);

void	handle_heredoc(t_minishell *minishell, int index)
{
	int		pid;
	int		cmd_pos;

	cmd_pos = has_cmd(minishell->cmd_table[index]);
	pipe(minishell->cmd_table[index]->fd);
	pid = fork();
	if (pid == 0)
		execute_heredoc(minishell->cmd_table[index]);
	else
	{
		close(minishell->cmd_table[index]->fd[1]);
		if (index > 0)
			close(minishell->cmd_table[index - 1]->fd[0]);
		get_exit_status(minishell, pid);
		// Check if there is a command for heredoc
		if (cmd_pos != -1)
			execute_heredoc_cmd(minishell, index);
	}
}

static void	execute_heredoc(t_cmd *cmd_table)
{
	char	*str;

	close(cmd_table->fd[0]);
	while (true)
	{
		str = readline("> ");
		if (ft_strcmp(cmd_table->deli, str) == EXIT_SUCCESS)
		{
			free(str);
			break ;
		}
		ft_fprintf(cmd_table->fd[1], "%s\n", str);
		free(str);
	}
	close(cmd_table->fd[1]);
	exit(EXIT_SUCCESS);
}

static void	execute_heredoc_cmd(t_minishell *minishell, int index)
{
	int		pid;
	t_cmd	new_cmd;

	pid = fork();
	if (pid == 0)
	{
		dup2(minishell->cmd_table[index]->fd[0], STDIN_FILENO);
		close(minishell->cmd_table[index]->fd[0]);
		if (has_cmd(minishell->cmd_table[index]) == 0)
		{
			new_cmd.cmd = assign_new_cmd_without_heredoc(minishell->cmd_table[index]->cmd);
			printf("newCMD: %s. %s.\n", new_cmd.cmd[0], new_cmd.cmd[1]);
			execute_cmd(&new_cmd, minishell->head_env);
		}
		else if (has_cmd(minishell->cmd_table[index]) == 1)
		{
			new_cmd.cmd = assign_new_cmd_without_heredoc(minishell->cmd_table[index]->cmd);
			echo(new_cmd.cmd);
		}
	}
	else
	{
		close(minishell->cmd_table[index]->fd[0]);
		get_exit_status(minishell, pid);
	}
}

static int	has_cmd(t_cmd *cmd_table)
{
	int	i;

	i = 0;
	while (cmd_table->cmd[i])
	{
		if (strcmp("cat", cmd_table->cmd[i]) == EXIT_SUCCESS)
			return (0);
		if (strcmp("echo", cmd_table->cmd[i]) == EXIT_SUCCESS)
			return (1);
		i++;
	}
	return (-1);
}

static char	**assign_new_cmd_without_heredoc(char **cmd)
{
	int		i;
	int		j;
	int		new_cmd_size;
	char	**new_cmd;

	i = 0;
	j = 0;
	new_cmd_size = 0;
	while (cmd[i])
	{
		if (ft_strcmp(cmd[i], "<<") == 0)
		{
			i += 2;
			continue ;
		}
		new_cmd_size++;
		i++;
	}
	new_cmd = ft_calloc(1, (new_cmd_size + 1) * sizeof(char *));
	i = 0;
	while (cmd[i])
	{
		if (ft_strcmp(cmd[i], "<<") == 0)
		{
			i += 2;
			continue ;
		}
		new_cmd[j] = cmd[i];
		j++;
		i++;
	}
	new_cmd[j] = NULL;
	return (new_cmd);
}

