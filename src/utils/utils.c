
#include "minishell.h"

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
