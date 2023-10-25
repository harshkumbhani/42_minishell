/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_lexer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkumbhan <hkumbhan@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 12:31:24 by hkumbhan          #+#    #+#             */
/*   Updated: 2023/10/25 14:19:34 by hkumbhan         ###   ########.fr       */
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
	int		i;

	current = (*head);
	while (current != NULL)
	{
		i = 0;
		printf("Token value : ");
		while (i < current->strlen)
		{
			printf("%c", current->start[i]);
			i++;
		}
		printf("\nToken type: %d\nStr : %s\nToken len: %d\nSpace_Flag: %d\n\n",
			current->token, current->start, current->strlen, current->space_flag);
		current = current->next;
	}
}
