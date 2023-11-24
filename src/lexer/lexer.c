/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkumbhan <hkumbhan@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 10:26:47 by hkumbhan          #+#    #+#             */
/*   Updated: 2023/11/24 16:08:12 by hkumbhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief Checks for open Quotes, Escape characters \ and ;
/// @param input Input string read from terminal
/// @return FALSE if open quotes or esc char found else TRUE
static int	check_input(char *input, t_minishell *minishell)
{
	char	c;

	c = '\0';
	while (*input != '\0')
	{
		if (c == '\0' && (*input == '\'' || *input == '\"'))
			c = *input;
		else if (c == *input)
			c = '\0';
		input++;
	}
	if (c == '\0')
		return (TRUE);
	ft_putendl_fd(QUOTES, STDERR_FILENO);
	minishell->exit_code = EXIT_FAILURE;
	return (FALSE);
}

/// @brief Creates redirection token
/// @param head Head node of the lexer lst
/// @param str str from the terminal
/// @return numbers of characters stored for redirs
static int	token_redirect(t_lexer **head, char *str)
{
	int	i;

	i = 0;
	if (str[i] != '\0' && str[i] == '<'
		&& str[i] != '\0' && str[i + 1] != '<')
		i = token_schar(head, &str[i], LESS);
	if (str[i] != '\0' && str[i] == '>'
		&& str[i] != '\0' && str[i + 1] != '>')
		i = token_schar(head, &str[i], GREATER);
	if (str[i] != '\0' && str[i] == '<'
		&& str[i] != '\0' && str[i + 1] == '<')
		i = token_dchar(head, &str[i], DOUBLE_LESS);
	if (str[i] != '\0' && str[i] == '>'
		&& str[i] != '\0' && str[i + 1] == '>')
		i = token_dchar(head, &str[i], DOUBLE_GREATER);
	return (i);
}

/// @brief Creates tokens and add them to a list
/// @param input string from terminal
/// @param minishell main lst with env
/// @return linked list of tokens
t_lexer	*tokenise(char *input, t_minishell *minishell)
{
	t_lexer	*head;
	int		i;

	i = 0;
	head = NULL;
	if (check_input(input, minishell) == FALSE)
		return (NULL);
	while (input[i] != '\0')
	{
		if (input[i] != '\0' && (ft_isspace(input[i]) == TRUE))
			i++;
		else if (input[i] == '\'')
			i += token_quote(&head, &input[i], SQUOTE);
		else if (input[i] == '\"')
			i += token_quote(&head, &input[i], DQUOTE);
		else if (input[i] == '|')
			i += token_schar(&head, &input[i], PIPE);
		else if (input[i] == '\\')
			i += token_schar(&head, &input[i], BACKSLASH);
		else if (input[i] == '>' || input[i] == '<')
			i += token_redirect(&head, &input[i]);
		else if (ft_isspace(input[i]) == FALSE)
			i += token_word(&head, &input[i]);
	}
	return (head);
}
