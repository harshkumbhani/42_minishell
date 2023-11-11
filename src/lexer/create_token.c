#include "minishell.h"

// && ft_isalnum(str[i] == TRUE)
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
		i++;
	}
	new->strlen = i;
	lst_add_back(head, new);
	return (i);
}

/// @brief Creates PIPE token
/// @param head Head node of the token list
/// @param str input str
/// @return number of characters in the token
int	token_pipe(t_lexer **head, char *str)
{
	t_lexer	*new;

	new = ft_calloc(1, sizeof(t_lexer));
	new->start = str;
	new->token = PIPE;
	new->strlen = 1;
	lst_add_back(head, new);
	return (1);
}

/// @brief Creates SINGLE QUOTE token
/// @param head head node of the lexer list
/// @param str the input string
/// @return number of characters in the token
int	token_squote(t_lexer **head, char *str)
{
	t_lexer	*new;
	int		i;

	i = 0;
	new = ft_calloc(1, sizeof(t_lexer));
	new->start = ++str;
	new->token = SQUOTE;
	while (str[i] != '\0' && str[i] != '\'')
		i++;
	new->strlen = i++;
	if (str[i] == '\'' || str[i] == '\"')
		new->not_space = TRUE;
	lst_add_back(head, new);
	return (i + 1);
}

/// @brief Creates DOUBLE QUOTE token
/// @param head head node of the lexer list
/// @param str the input string
/// @return number of characters in the token 
int	token_dquote(t_lexer **head, char *str)
{
	t_lexer	*new;
	int		i;

	i = 0;
	new = ft_calloc(1, sizeof(t_lexer));
	new->start = ++str;
	new->token = DQUOTE;
	while (str[i] != '\0' && str[i] != '\"')
		i++;
	new->strlen = i++;
	if (str[i] == '\'' || str[i] == '\"')
		new->not_space = TRUE;
	lst_add_back(head, new);
	return (i + 1);
}

/// @brief Creates BACKSLASH token
/// @param head Head node of the lexer list
/// @param str input string
/// @return character in the token
int	token_backslash(t_lexer **head, char *str)
{
	t_lexer	*new;

	new = ft_calloc(1, sizeof(t_lexer));
	new->start = str;
	new->token = BACKSLASH;
	new->strlen = 1;
	lst_add_back(head, new);
	return (1);
}
