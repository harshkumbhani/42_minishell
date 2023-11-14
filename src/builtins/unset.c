/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwenz <cwenz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 16:59:19 by cwenz             #+#    #+#             */
/*   Updated: 2023/11/13 22:05:06 by cwenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_key_valid(char *key);

/**
 * @brief Removes a variable from the env linked list.
 * 	Loops through the linked list searching for the given
 * 	key. If the key is found, it frees the node and updates
 * 	the linked list to maintain integrity.
 * @param head A pointer to the head node.
 * @param key The key/variable to remove.
 * @return 1 if the last key was invalid, else 0 if the last key was valid.
 */
int	unset(t_env **head, char **key)
{
	int	i;
	int	ret;

	i = 1;
	while (key[i])
	{
		if (!is_key_valid(key[i]))
		{
			error_msg("unset", key[i], IDENTIFIER);
			ret = 1;
		}
		else
		{
			remove_key(key[i], head);
			ret = 0;
		}
		i++;
	}
	return (ret);
}

static bool	is_key_valid(char *key)
{
	int	i;

	i = 0;
	while (key[i])
	{
		if (ft_isalnum(key[i]) == 0 && key[i] != '_')
			return (false);
		i++;
	}
	return (true);
}

void	remove_key(char *key, t_env **head)
{
	t_env *temp;
	t_env *prev;

	prev = NULL;
	temp = *head;
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
