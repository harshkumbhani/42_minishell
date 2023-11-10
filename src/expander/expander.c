#include "minishell.h"

int	check_var(char c)
{
	if (ft_isdigit(c) == TRUE || c != '_'
		|| ft_isalpha(c) != TRUE)
		return (TRUE);
	return (FALSE);
}

int	special_var(char c, char **ret, t_minishell *minishell)
{
	char	*tmp;

	tmp = ft_itoa(minishell->exit_code);
	*ret = ft_strjoin(*ret, tmp);
	free(tmp);
	return (2);
}

char	*expander(t_lexer *lexer, t_minishell *minishell)
{
	char	*ret;
	 char	*tmp;
	int		i;
	int		j;

	i = 0;
	ret = NULL;
	tmp = NULL;
	while (i < lexer->strlen && lexer->start[i] != '$')
		i++ ;
	if (i == lexer->strlen)
		return (ft_strndup(lexer->start, i));
	ret = ft_strndup(lexer->start, i);
	while (i < lexer->strlen)
	{
		if (lexer->start[i] == '$' && lexer->start[i + 1] == '?')
			i += special_var(&lexer->start[i], &ret, minishell);
		if (lexer->start[i] == '$' && check_var(lexer->start[i + 1]) == TRUE)
			i = i + 2;
		else
		{
			j = 0;
			while (i + j < lexer->strlen && lexer->start[i + j] != '$')
				j++;
			tmp = ft_strndup(&lexer->start[i], j);
			ret = ft_strjoin(ret, tmp);
			free(tmp);
			i += j;
		}
	}
	printf("\nExpanded string: %s\n", ret);
	return (ret);
}
