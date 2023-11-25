/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwenz <cwenz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 16:37:48 by cwenz             #+#    #+#             */
/*   Updated: 2023/11/25 14:46:46 by cwenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	update_pwd(t_env **head, char *old_dir);

/// @brief Changes the working directory of the current process
///
/// It also updates the OLDPWD and PWD env variables.
/// @param head The pointer to the env linked list
/// @param path The path to change the working directory to
/// @return EXIT_SUCCESS if it succeeds, else EXIT_FAILURE
int	cd(t_env **head, char *path)
{
	int		len;
	char	*old_dir;

	if (!path || !*path)
	{
		path = getenv("HOME");
		if (!path)
			return (EXIT_FAILURE);
	}
	len = ft_strlen(path);
	if (len > 0 && path[len - 1] == '\n')
		path[len - 1] = '\0';
	old_dir = getcwd(NULL, 0);
	if (chdir(path) != EXIT_SUCCESS)
	{
		error_msg(path, NULL, strerror(errno));
		return (EXIT_FAILURE);
	}
	update_pwd(head, old_dir);
	free(old_dir);
	return (EXIT_SUCCESS);
}

/// @brief Updates the PWD and OLDPWD env variables
/// @param head A pointer to th env linked list
/// @param old_dir The old directory to set the OLDPWD to.
static void	update_pwd(t_env **head, char *old_dir)
{
	char	*new_dir;
	t_env	*pwd_env;
	t_env	*oldpwd_env;

	oldpwd_env = find_env_key(*head, "OLDPWD");
	if (oldpwd_env)
	{
		free(oldpwd_env->value);
		free(oldpwd_env->full_string);
		oldpwd_env->value = ft_strdup(old_dir);
		oldpwd_env->full_string = ft_strjoin("OLDPWD=", old_dir);
	}
	new_dir = getcwd(NULL, 0);
	pwd_env = find_env_key(*head, "PWD");
	free(pwd_env->value);
	free(pwd_env->full_string);
	pwd_env->value = ft_strdup(new_dir);
	pwd_env->full_string = ft_strjoin("PWD=", new_dir);
	free(new_dir);
}
