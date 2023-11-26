/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkumbhan <hkumbhan@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 11:31:40 by hkumbhan          #+#    #+#             */
/*   Updated: 2023/11/26 12:23:10 by hkumbhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_pipes(t_lexer **lexer)
{
	int		i;
	t_lexer	*current;

	i = 0;
	current = *lexer;
	if (current == NULL)
		return (i);
	while (current != NULL)
	{
		if (current->token == PIPE)
			i++;
		current = current->next;
	}
	return (i);
}

int	count_words(t_lexer **lexer)
{
	t_lexer	*lex;
	int		i;

	i = 0;
	lex = *lexer;
	while (lex != NULL && lex->token != PIPE)
	{
		if (lex->token == WORD || lex->token == SQUOTE
			|| lex->token == DQUOTE)
			i++;
		lex = lex->next;
	}
	return (i);
}

int	t_check(t_token token_type)
{
	if (token_type == WORD || token_type == DQUOTE
		|| token_type == SQUOTE)
		return (TRUE);
	return (FALSE);
}
