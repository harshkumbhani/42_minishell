
#include "minishell.h"

static void	process_string(t_env **head, char *str);
static bool	is_key_valid(char *str);
static char	*get_key(char *str);

int	export(t_env **head, char **str)
{
	int	i;

	i = 1;
	if (!str[1])
	{
		print_env_ascending(*head);
		return (EXIT_SUCCESS);
	}
	while (str[i])
	{
		if (!is_key_valid(str[i]))
			ft_fprintf(STDERR_FILENO, "minishell: export: \'%s\': is not a valid identifier\n", str[i]);
		else
			process_string(head, str[i]);
		i++;
	}
	return (EXIT_SUCCESS);
}

static void	process_string(t_env **head, char *str)
{
	char	*key;
	char	*equal_sign;
	char	*full_string;
	char	*value;

	full_string = ft_strdup(str);
	equal_sign = ft_strchr(full_string, '=');
	key = ft_strndup(full_string, equal_sign - full_string);
	value = ft_strdup(equal_sign + 1);
	if (!key || !equal_sign || !full_string || !value)
	{
		if (key)
			free(key);
		if (full_string)
			free(full_string);
		if (value)
			free(value);
		return ;
	}
	unset(head, key);
	add_env_node(head, key, full_string, value);
}

static bool	is_key_valid(char *str)
{
	int		i;
	char	*key;

	key = get_key(str);
	if (!key)
		return (false);
	if (!ft_isalpha(key[0]) && key[0] != '_')
		return (free(key), false);
	i = 1;
	while (key[i])
	{
		if (ft_isalnum(key[i]) == 0 && key[i] != '_')
			return (free(key), false);
		i++;
	}
	return (free(key), true);
}

static char	*get_key(char *str)
{
	char	*key;
	char	*equal_sign;
	char	*full_string;

	full_string = ft_strdup(str);
	if (!full_string)
		return (NULL);
	equal_sign = ft_strchr(full_string, '=');
	if (!equal_sign)
		return (free(full_string), NULL);
	key = ft_strndup(full_string, equal_sign - full_string);
	if (!key)
		return (free(full_string), NULL);
	free(full_string);
	return (key);
}