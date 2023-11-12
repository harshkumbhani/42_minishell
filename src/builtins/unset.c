/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwenz <cwenz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 16:59:19 by cwenz             #+#    #+#             */
/*   Updated: 2023/11/12 16:59:27 by cwenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Removes a variable from the env linked list.
 * 	Loops through the linked list searching for the given
 * 	key. If the key is found, it frees the node and updates
 * 	the linked list to maintain integrity.
 * @param head A pointer to the head node.
 * @param key The key/variable to remove.
 * @return EXIT_SUCCESS regardless if it finds the key or not
 */
int	unset(t_env **head, const char *key)
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
			return (EXIT_SUCCESS);
		}
		prev = temp;
		temp = temp->next;
	}
	return (EXIT_SUCCESS);
}
