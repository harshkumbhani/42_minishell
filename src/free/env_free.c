/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwenz <cwenz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 15:07:48 by cwenz             #+#    #+#             */
/*   Updated: 2023/11/25 15:07:51 by cwenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief Frees all allocated memory from the env linked list.
/// @param head A pointer to the head node of the linked list.
void	free_env_linked_list(t_env	*head)
{
	t_env	*temp;
	while (head)
	{
		temp = head;
		head = head->next;
		free_env_node(temp);
	}
}

/// @brief Frees individual node for the env linked list.
/// @param node The node to be freed.
void	free_env_node(t_env *node)
{
	free(node->key);
	free(node->value);
	free(node->full_string);
	free(node);
}

/// @brief Frees the array of env variables.
/// @param envp The 2D array of env variables that should be freed.
void	free_env_array(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		free(envp[i]);
		i++;
	}
	free(envp);
}
