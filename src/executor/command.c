/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwenz <cwenz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 18:30:13 by cwenz             #+#    #+#             */
/*   Updated: 2023/11/24 18:30:14 by cwenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*resolve_cmd_path(t_cmd *cmd, t_env *head_env);
static char	*find_command_in_path(char *cmd, char **envp);
static void	handle_command_execution_error(t_cmd *cmds, char *path);
static char	*check_for_file_command(t_cmd *cmd);

void	execute_cmd(t_cmd *cmds, t_env *head_env)
{
	char	*path;
	char	**env;

	path = resolve_cmd_path(cmds, head_env);
	env = copy_env(head_env);
	if (execve(path, cmds->cmd, env) == -1)
	{
		free_env_array(env);
		handle_command_execution_error(cmds, path);
	}
}

static char	*resolve_cmd_path(t_cmd *cmd, t_env *head_env)
{
	t_env	*path_node;
	char	**envp;
	char	*path;

	path = check_for_file_command(cmd);
	if (path)
		return (path);
	envp = NULL;
	path_node = find_env_key(head_env, "PATH");
	if (path_node)
		envp = ft_split(path_node->value, ':');
	path = find_command_in_path(cmd->cmd[0], envp);
	if (!path)
		return (NULL);
	free(envp);
	return (path);
}

static char	*check_for_file_command(t_cmd *cmd)
{
	char	*path;

	path = strjoin_pipex(cmd->cmd[0], "");
	if (access(path, F_OK) == 0)
		return (path);
	free(path);
	return (NULL);
}

static char	*find_command_in_path(char *cmd, char **envp)
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
		{
			i++;
			continue ;
		}
		if (access(path, F_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	return (NULL);
}

static void	handle_command_execution_error(t_cmd *cmds, char *path)
{
	int			exit_code;

	if (!path)
	{
		if (ft_strchr(cmds->cmd[0], '/'))
			error_msg(cmds->cmd[0], NULL, NO_DIR);
		else
			error_msg(cmds->cmd[0], NULL, NOT_FOUND);
		exit_code = 127;
	}
	else
		exit_code = handle_file_execution_errors(path);
	free(path);
	exit(exit_code);
}
