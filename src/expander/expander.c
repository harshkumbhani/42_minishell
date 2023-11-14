#include "minishell.h"

int	check_var(char c)
{
	if (ft_isalnum(c) == TRUE || c == '_')
		return (TRUE);
	return (FALSE);
}

int	special_var(char **ret, t_minishell *minishell)
{
	char	*tmp;

	tmp = ft_itoa(minishell->exit_code);
	*ret = ft_strjoin(*ret, tmp);
	free(tmp);
	return (2);
}

int	special_char(char **ret, char *str)
{
	char	*tmp;

	tmp = NULL;
	tmp = ft_strndup(str, 2);
	*ret = ft_strjoin_gnl(*ret, tmp);
	free(tmp);
	return (2);
}

int	get_var(char **ret, char *str, t_minishell *minshell)
{
	int		i;
	t_env	*env;

	i = 0;
	env = minshell->head_env;
	while (str[i] == '_' || ft_isalnum(str[i]) == TRUE)
		i++;
	while (env != NULL)
	{
		if ((size_t)i == ft_strlen(env->key))
		{
			if (ft_strncmp(str, env->key, i) == 0)
			{
				*ret = ft_strjoin_gnl(*ret, env->value);
				break ;
			}
		}
		env = env->next;
	}
	return (i + 1);
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
			i += special_var(&ret, minishell);
		else if (lexer->start[i] == '$' && ft_isdigit(lexer->start[i + 1]) == TRUE)
			i += 2;
		else if (lexer->start[i] == '$' && check_var(lexer->start[i + 1]) == FALSE)
			i += special_char(&ret, &lexer->start[i]);
		else if (lexer->start[i] == '$' && check_var(lexer->start[i + 1]) == TRUE)
			i += get_var(&ret, &lexer->start[i + 1], minishell);
		else
		{
			j = 0;
			while (i + j < lexer->strlen && lexer->start[i + j] != '$')
				j++;
			tmp = ft_strndup(&lexer->start[i], j);
			ret = ft_strjoin_gnl(ret, tmp);
			free(tmp);
			i += j;
		}
	}
	//printf("Expanded string: %s\n", ret);
	return (ret);
}
