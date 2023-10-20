
#include "minishell.h"

void	unset(t_env *head, char *key)
{
	t_env	*temp;
	t_env	*prev;

	temp = head;
	while (temp)
	{
		prev = temp;
		if (ft_strncmp(temp->key, key, ft_strlen(temp->key)))
		{
			prev->next = temp->next;
			free(temp);
			return ;
		}
		temp = temp->next;
	}
}
