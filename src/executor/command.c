#include "minishell.h"

void	execute_cmd(t_cmd *cmds, t_env *head_env)
{
	t_env	*path_node;
	char	*path;
	char	**envp;

	path_node = find_env_key(head_env, "PATH");
	envp = ft_split(path_node->value, ':');
	path = find_cmd_path(cmds, envp);
	if (!path)
	{
		error_msg(cmds->cmd[0], NOT_FOUND);
		free_env_array(envp);
		exit(127);
	}
	if (execve(path, cmds->cmd, envp) == -1)
	{
		error_msg(cmds->cmd[0], strerror(errno));
		free(path);
		free_env_array(envp);
		exit(errno);
	}
}

// Todo: Check if i can access the file and handle appropraitely??
char	*find_cmd_path(t_cmd *cmd, char **envp)
{
	char	*path;
	char	*temp;
	int		i;

	path = strjoin_pipex(cmd->cmd[0], "");
	if (access(path, F_OK | X_OK) == 0)
		return (path);
	free(path);
	i = 0;
	while (envp[i])
	{
		temp = strjoin_pipex(envp[i], "/");
		if (!temp)
			return (NULL);
		path = strjoin_pipex(temp, cmd->cmd[0]);
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
