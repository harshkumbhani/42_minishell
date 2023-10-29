
#include "minishell.h"

/**
 * @brief Copies the envp to a linked list format.
 * @param envp A double pointer that holds all env variables.
 * @param head A pointer to the first node in the env linked list.
 * @return The head node if everything was successful or NULL.
 */
int	copy_env_to_linked_list(char **envp, t_env **head)
{
	int		i;

	i = 0;
	while (envp[i])
	{
		export(head, envp[i]);
		if (!(*head))
		{
			free_env_linked_list(*head);
			return (EXIT_FAILURE);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

int	add_env_node(t_env **head, char *key, char *full_string, char *value)
{
	t_env	*temp;
	t_env	*new_node;

	new_node = ft_calloc(1, sizeof(t_env));
	if (!new_node)
		return (EXIT_FAILURE);
	new_node->key = key;
	new_node->full_string = full_string;
	new_node->value = value;
	new_node->next = NULL;

	if (!(*head))
		*head = new_node;
	else
	{
		temp = *head;
		while (temp->next)
			temp = temp->next;
		temp->next = new_node;
	}
	return (EXIT_SUCCESS);
}

/**
 * @brief Finds the node which holds the given key.
 * @param head A pointer to the first head of the env array
 * @param key The key to search for.
 * @return The node which holds the given key, else NULL if not found
 */
t_env	*find_env_key(t_env *head, char *key)
{
	t_env	*temp;

	temp = head;
	while (temp)
	{
		if (strcmp(temp->key, key) == EXIT_SUCCESS)
			return (temp);
		temp = temp->next;
	}
	return (NULL);
}

/**
 * @brief Counts the number of env variables stored in the linked list
 * @param head A pointer to the first node in the linked list
 * @return The amount of env variables stored in the linked list.
 */
int	count_env_variables(t_env *head)
{
	int		i;
	t_env	*temp;

	temp = head;
	i = 0;
	while (temp)
	{
		i++;
		temp = temp->next;
	}
	return (i);
}
