
#include "minishell.h"

/**
 * @brief Removes a variable from the env linked list.
 * 	Loops through the linked list searching for the given
 * 	key. If the key is found, it frees the node and updates
 * 	the linked list to maintain integrity.
 * @param head A pointer to the head node.
 * @param key The key/variable to remove.
 */
void	unset(t_env **head, const char *key)
{
	t_env	*temp;
	t_env	*prev;

	temp = *head;
	prev = NULL;
	while (temp)
	{
		if (ft_strcmp(temp->key, key) == 0)
		{
			if (!prev)
				*head = temp->next;
			else
				prev->next = temp->next;
			prev->next = temp->next;
			free_env_node(temp);
			return ;
		}
		prev = temp;
		temp = temp->next;
	}
}