
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

	tmp = ft_itoa(*minishell->exit_code);
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
