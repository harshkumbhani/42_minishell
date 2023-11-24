/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkumbhan <hkumbhan@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 09:32:11 by hkumbhan          #+#    #+#             */
/*   Updated: 2023/11/24 16:06:35 by hkumbhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief Creates word token
/// @param head Head node of the token list
/// @param str input string
/// @return number of characters in the token
int	token_word(t_lexer **head, char *str)
{
	int		i;
	t_lexer	*new;

	i = 0;
	new = ft_calloc(1, sizeof(t_lexer));
	new->start = str;
	new->token = WORD;
	while (str[i] != '\0' && ft_isspace(str[i]) == FALSE)
	{
		if (str[i] == '>' || str[i] == '<')
			break ;
		else if (str[i] == '\'' || str[i] == '\"')
		{
			new->not_space = TRUE;
			break ;
		}
		i++;
	}
	new->strlen = i;
	lst_add_back(head, new);
	return (i);
}

/// @brief Creates tokens with one character
/// @param head head node of the lexer
/// @param str input str from the terminal
/// @param token TOKEN type
/// @return character in the token, in this case 1
int	token_schar(t_lexer **head, char *str, t_token token)
{
	t_lexer	*new;

	new = ft_calloc(1, sizeof(t_lexer));
	new->start = str;
	new->token = token;
	new->strlen = 1;
	lst_add_back(head, new);
	return (1);
}

/// @brief Creates tokens with two character
/// @param head head node of the lexer
/// @param str input str from the terminal
/// @param token TOKEN type
/// @return character in the token, in this case 2
int	token_dchar(t_lexer **head, char *str, t_token token)
{
	t_lexer	*new;

	new = ft_calloc(1, sizeof(t_lexer));
	new->start = str;
	new->token = token;
	new->strlen = 2;
	lst_add_back(head, new);
	return (2);
}

/// @brief Creates the token with quotes
/// @param head head node of the lexer
/// @param str input str
/// @param token SQUOTE || DQUOTE
/// @return number of characters within the quotes
int	token_quote(t_lexer **head, char *str, t_token token)
{
	t_lexer	*new;
	int		i;

	i = 0;
	new = ft_calloc(1, sizeof(t_lexer));
	new->start = ++str;
	new->token = token;
	while (str[i] != '\0' && str[i] != '\"')
		i++;
	new->strlen = i++;
	if (str[i] != '\0' && ((str[i] == '\'' || str[i] == '\"')
			|| ft_isspace(str[i]) == FALSE))
		new->not_space = TRUE;
	lst_add_back(head, new);
	return (i + 1);
}
