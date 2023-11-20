#include "minishell.h"

static char	**copy_env(t_env *head);
static char	*resolve_cmd_path(t_cmd *cmd, t_env *head_env);
static char	*get_cmd(t_cmd *cmd, char **envp);
static char	*search_cmd_in_path(char *cmd, char **envp);

void	execute_cmd(t_cmd *cmds, t_env *head_env)
{
	char	*path;
	char	**env;

	path = resolve_cmd_path(cmds, head_env);
	env = copy_env(head_env);
	if (!path)
	{
		error_msg(cmds->cmd[0], NULL, NOT_FOUND);
		free_env_array(env);
		exit(127);
	}
	if (execve(path, cmds->cmd, env) == -1)
	{
		error_msg(cmds->cmd[0], NULL, strerror(errno));
		free(path);
		free_env_array(env);
		exit(errno);
	}
}

static char	*resolve_cmd_path(t_cmd *cmd, t_env *head_env)
{
	t_env	*path_node;
	char	**envp;
	char	*path;

	envp = NULL;
	path_node = find_env_key(head_env, "PATH");
	if (path_node)
		envp = ft_split(path_node->value, ':');
	path = get_cmd(cmd, envp);
	if (!path)
		return (free(envp), NULL);
	free(envp);
	return (path);
}

static char	*get_cmd(t_cmd *cmd, char **envp)
{
	char	*path;

	path = strjoin_pipex(cmd->cmd[0], "");
	if (access(path, F_OK | X_OK) == 0)
		return (path);
	free(path);
	path = search_cmd_in_path(cmd->cmd[0], envp);
	if (!path && !envp)
	{
		error_msg(cmd->cmd[0], NULL, NO_DIR);
		exit(127);
	}
	return (path);
}

static char	*search_cmd_in_path(char *cmd, char **envp)
{
	int		i;
	char	*temp;
	char	*path;

	i = 0;
	while (envp && envp[i])
	{
		temp = strjoin_pipex(envp[i], "/");
		if (!temp)
			return (NULL);
		path = strjoin_pipex(temp, cmd);
		if (!path)
			return (NULL);
		free(temp);
		if (access(path, F_OK | X_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	return (NULL);
}

static char	**copy_env(t_env *head)
{
	int		i;
	char	**env;
	t_env	*temp;

	i = count_env_variables(head);
	temp = head;
	env = (char **)ft_calloc(i + 1, sizeof(char *));
	if (!env)
		return (NULL);
	i = 0;
	while (temp)
	{
		env[i] = ft_strdup(temp->full_string);
		i++;
		temp = temp->next;
	}
	env[i] = NULL;
	return (env);
}
