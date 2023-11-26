/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwenz <cwenz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 18:30:13 by cwenz             #+#    #+#             */
/*   Updated: 2023/11/26 11:13:58 by cwenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*resolve_cmd_path(t_cmd *cmd, t_env *head_env);
static char	*find_command_in_path(char *cmd, char **envp);
static void	handle_command_execution_error(t_cmd *cmds, char *path);
static char	*check_for_file_command(t_cmd *cmd);

/// @brief Executes a command in `execve`. This function gets the filesystem
/// path for the command stored in `cmds`. It also copies the env linked list
/// to a `char**` format to pass to `execve. If `execve` fails, it frees the
/// `char** env` and returns an appropriate error message and exit code.
/// @param cmds A pointer which holds the command to execute and potentially
/// its options.
/// @param head_env A pointer to the linked list which stores all env
/// variables.
/// @note See `src/executor/command.c` for more details.
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

/// @brief Finds the filesystem path for the given command.
/// @param cmd The command to search for.
/// @param head_env A linked list that contains the `env` variables
/// @return If the path is found it returns a pointer to it, else NULL.
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

/// @brief Checks if the given command is an absolute path.
/// @param cmd The command to check.
/// @return The path if found, else NULL.
static char	*check_for_file_command(t_cmd *cmd)
{
	char	*path;

	path = strjoin_pipex(cmd->cmd[0], "");
	if (access(path, F_OK) == 0)
		return (path);
	free(path);
	return (NULL);
}

/// @brief Finds the system file path for the given command.
/// It gets the `PATH env` variable and splits it
/// @param cmd The command to search for.
/// @param envp The `char **` that holds the PATH variable
/// @return The path (if found) or NULL.
static char	*find_command_in_path(char *cmd, char **envp)
{
	int		i;
	char	*temp;
	char	*path;

	i = 0;
	while (envp && envp[i] && cmd[0] != '\0')
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

/// @brief This function decides the appropriate error message to
/// display and the exit code to use based on whether the command's
/// path is valid and if specific conditions are met. 
/// @param cmds The command structure containing the command
/// @param path The filesystem path to the command to be executed. if 'NULL`
/// the command is treated as not found or a directory error.
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
