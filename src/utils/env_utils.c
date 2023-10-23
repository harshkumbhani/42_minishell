
#include "minishell.h"


static t_env	*add_env_node(t_env *head, char *key, char *full_string, char *value);

/**
 * @brief Copies the envp to a linked list format.
 * @param envp A double pointer that holds all env variables.
 * @param head A pointer to the first node in the env linked list.
 * @return The head node if everything was successful or NULL.
 */
t_env	*copy_env_to_linked_list(char **envp, t_env *head)
{
	int		i;

	i = 0;
	while (envp[i])
	{
		head = add_env_row(head, envp[i]);
		if (!head)
		{
			free_env_linked_list(head);
			return (NULL);
		}
		i++;
	}
	return (head);
}

/**
 * @brief Adds the given string to the env linked list.
 * @param head The first node of the env linked list.
 * @param str The string to be added to the end of the linked list
 * @return The head node if successful, else NULL.
 */
t_env	*add_env_row(t_env *head, char *str)
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
		return (NULL);
	}
	return (add_env_node(head, key, full_string, value));
}

static t_env	*add_env_node(t_env *head, char *key, char *full_string, char *value)
{
	t_env	*temp;
	t_env	*new_node;

	new_node = ft_calloc(1, sizeof(t_env));
	if (!new_node)
		return (NULL);
	new_node->key = key;
	new_node->full_string = full_string;
	new_node->value = value;
	new_node->next = NULL;

	if (!head)
		return (new_node);
	temp = head;
	while (temp->next)
		temp = temp->next;
	temp->next = new_node;
	return (head);
}
