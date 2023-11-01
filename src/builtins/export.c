
#include "minishell.h"

/**
 * @brief Adds the given string to the env linked list.
 * @param head The first node of the env linked list.
 * @param str The string to be added to the end of the linked list
 * @return EXIT_SUCESS if everything was ok, else EXIT_FAILURE
 */
int	export(t_env **head, char *str)
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
		return (EXIT_FAILURE);
	}
	// If there is a duplicate key, remove the exisiting variable and replace with new
	unset(head, key);
	add_env_node(head, key, full_string, value);
	return (EXIT_SUCCESS);
}
