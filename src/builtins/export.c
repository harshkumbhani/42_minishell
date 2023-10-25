
#include "minishell.h"

/**
 * @brief Adds the given string to the env linked list.
 * @param head The first node of the env linked list.
 * @param str The string to be added to the end of the linked list
 * @return The head node if successful, else NULL.
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
	add_env_node(head, key, full_string, value);
	return (EXIT_SUCCESS);
}
