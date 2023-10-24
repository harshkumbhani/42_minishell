
#include "minishell.h"

static void	update_pwd(t_env **head, char *old_dir);


int	cd(t_env **head)
{
	int		len;
	char	*old_dir;
	char 	*path = "src"; // remove this variable and use cmd struct later on
	
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
		perror("Chdir() failed!\n");
		return (EXIT_FAILURE);
	}
	update_pwd(head, old_dir);
	free(old_dir);
	return (EXIT_SUCCESS);
}

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
