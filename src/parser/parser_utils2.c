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

// char	*expander(t_lexer *lexer, t_env **env)
// {
// 	t_env	*envp;
// 	char	*ret;
// 	int		i;

// 	i = 0;
// 	ret = NULL;
// 	envp = *env;
// 	while (i < lexer->strlen && lexer->start[i] != '$')
// 		i++;
// 	if (i == lexer->strlen)
// 		ret = ft_strndup(lexer->start, i);
// 	//else
// 	//{
// 	//	i--;
		
// 	//}
// 	return (ret);
// }
