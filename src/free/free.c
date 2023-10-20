
#include "minishell.h"

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

