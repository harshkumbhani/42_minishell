/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwenz <cwenz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 10:26:47 by hkumbhan          #+#    #+#             */
/*   Updated: 2023/11/24 16:31:36 by cwenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief Checks for open Quotes, Escape characters \ and ;
/// @param input Input string read from terminal
/// @return FALSE if open quotes or esc char found else TRUE
int	check_input(char *input, t_minishell *minishell)
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
	set_exit_code(1);
	(void)minishell;
	return (FALSE);
}

int	token_redirect(t_lexer **head, char *str)
{
	int	i;

	i = 0;
	if (str[i] != '\0' && str[i] == '<'
		&& str[i] != '\0' && str[i + 1] != '<')
		i = create_less(head, &str[i]);
	if (str[i] != '\0' && str[i] == '>'
		&& str[i] != '\0' && str[i + 1] != '>')
		i = create_greater(head, &str[i]);
	if (str[i] != '\0' && str[i] == '<'
		&& str[i] != '\0' && str[i + 1] == '<')
		i = create_dbless(head, &str[i]);
	if (str[i] != '\0' && str[i] == '>'
		&& str[i] != '\0' && str[i + 1] == '>')
		i = create_dbgreater(head, &str[i]);
	return (i);
}

/// @brief Creates tokens and add them to a list
/// @param input 
/// @return 
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
			i += token_squote(&head, &input[i]);
		else if (input[i] == '\"')
			i += token_dquote(&head, &input[i]);
		else if (input[i] == '|')
			i += token_pipe(&head, &input[i]);
		else if (input[i] == '\\')
			i += token_backslash(&head, &input[i]);
		else if (input[i] == '>' || input[i] == '<')
			i += token_redirect(&head, &input[i]);
		else if (ft_isspace(input[i]) == FALSE)
			i += token_word(&head, &input[i]);
	}
	return (head);
}
