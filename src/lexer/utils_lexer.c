/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_lexer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkumbhan <hkumbhan@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 09:32:35 by hkumbhan          #+#    #+#             */
/*   Updated: 2023/11/14 09:32:36 by hkumbhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	lst_add_back(t_lexer **head, t_lexer *new_node)
{
	t_lexer	*current;

	current = *head;
	if (*head == NULL)
		*head = new_node;
	else
	{
		while (current->next != NULL)
			current = current->next;
		current->next = new_node;
	}
}

void	lst_del(t_lexer **head)
{
	t_lexer	*current;

	current = *head;
	if (!current)
		return ;
	while (*head != NULL)
	{
		*head = (*head)->next;
		free(current);
		current = NULL;
		current = *head;
	}
	(*head) = NULL;
	return ;
}

void	print_list(t_lexer **head)
{
	t_lexer	*current;

	current = (*head);
	while (current != NULL)
	{
		write(1, "Token value: ", ft_strlen("Token value: "));
		write(1, current->start, current->strlen);
		printf("\nToken type: %d\nStr : %s\nToken len: %d\nnot_space: %d\n\n",
			current->token, current->start, current->strlen,
			current->not_space);
		current = current->next;
	}
}
