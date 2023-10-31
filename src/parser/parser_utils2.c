#include "minishell.h"

int	count_words(t_lexer **lexer)
{
	t_lexer	*lex;
	int		i;

	i = 0;
	lex = *lexer;
	while (lex != NULL)
	{
		if (lex->token == WORD || lex->token == SQUOTE
				|| lex->token == DQUOTE)
			i++;
		lex = lex->next;
	}
	printf("number of words : %d\n", i);
	return (i);
}

char	*expander(t_lexer *lexer, t_env **env)
{
	t_env	*envp;
	char	*ret;
	size_t	i;

	i = 0;
	ret = NULL;
	envp = *env;
	while (lexer->start[i] != '\0' && lexer->start[i] != '$')
		i++;
	if (lexer->start[i] == '\0')
		ret = ft_strndup(lexer->start, i);
	else
	{
		i--;
		
	}
	return (ret);
}
