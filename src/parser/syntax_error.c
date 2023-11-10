#include "minishell.h"

int	ft_error(t_minishell *minishell, t_token token)
{
	static char	*token_str[] = {
		"WORD", "|", "SQUOTE", "DQUOTE",
		"BACKSLASH", "<", ">",
		"<<", ">>"
	};

	ft_putstr_fd(SYNTAX, STDERR_FILENO);
	ft_putendl_fd(token_str[token], STDERR_FILENO);
	minishell->exit_code = 258;
	return (FAIL);
}

int	is_meta_token(t_lexer *lexer)
{
	if (lexer->token == PIPE || lexer->token == LESS
		|| lexer->token == GREATER)
		return (TRUE);
	else if (lexer->token == DOUBLE_GREATER
		|| lexer->token == DOUBLE_LESS)
		return (TRUE);
	return (FALSE);
}

int	is_redirect(t_lexer *lexer)
{
	if (lexer->token == LESS || lexer->token == GREATER
		|| lexer->token == DOUBLE_GREATER
		|| lexer->token == DOUBLE_LESS)
		return (TRUE);
	return (FALSE);
}

int	syntax_checker(t_lexer **lexer, t_minishell *minishell)
{
	t_lexer	*lex;

	lex = (*lexer);
	if (lex == NULL)
		return (SUCCESS);
	if (lex->token == PIPE)
		return (ft_error(minishell, PIPE));
	while (lex != NULL)
	{
		if (is_meta_token(lex) && lex->next == NULL)
			return (ft_error(minishell, lex->token));
		else if (is_redirect(lex) && is_meta_token(lex->next))
			return (ft_error(minishell, lex->next->token));
		else if (lex->token == PIPE && is_redirect(lex) == TRUE)
			lex = lex->next ;
		lex = lex->next;
	}
	return (SUCCESS);
}
