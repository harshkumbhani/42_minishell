
#include "minishell.h"

/**
 * @brief Frees all allocated memory from the env linked list.
 * @param head A pointer to the head node of the linked list.
 */
void	free_env_linked_list(t_env	*head)
{
	t_env	*temp;
	while (head)
	{
		temp = head;
		head = head->next;
		free(temp->key);
		free(temp->value);
		free(temp->full_string);
		free(temp);
	}
}

