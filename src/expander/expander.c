#include "minishell.h"

static int	get_var(char **ret, char *str, t_minishell *minshell)
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

static void	ft_join_rest(int *i, char *str, int strlen, char **ret)
{
	char	*tmp;
	int		j;

	tmp = NULL;
	j = 0;
	while ((*i) + j < strlen && str[*i + j] != '$')
		j++;
	tmp = ft_strndup(&str[*i], j);
	(*ret) = ft_strjoin_gnl(*ret, tmp);
	free(tmp);
	(*i) += j;
}

char	*expander(char *str, int strlen,t_minishell *minishell)
{
	char	*ret;
	int		i;

	i = 0;
	ret = NULL;
	while (i < strlen && str[i] != '$')
		i++ ;
	if (i == strlen)
		return (ft_strndup(str, i));
	ret = ft_strndup(str, i);
	while (i < strlen)
	{
		if (str[i] == '$' && str[i + 1] == '?')
			i += special_var(&ret, minishell);
		else if (str[i] == '$' && ft_isdigit(str[i + 1]) == TRUE)
			i += 2;
		else if (str[i] == '$' && check_var(str[i + 1]) == FALSE)
			i += special_char(&ret, &str[i]);
		else if (str[i] == '$' && check_var(str[i + 1]) == TRUE)
			i += get_var(&ret, &str[i + 1], minishell);
		else
			ft_join_rest(&i, str, strlen, &ret);
	}
	printf("Expanded string: %s\n", ret);
	return (ret);
}
