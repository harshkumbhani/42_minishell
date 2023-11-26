/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkumbhan <hkumbhan@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 16:08:42 by hkumbhan          #+#    #+#             */
/*   Updated: 2023/11/26 12:18:30 by hkumbhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief Function checks for the var after '$' char and replaces the var with
///			its value
/// @param ret address of the orginal return string 
/// @param str string starting after $ char
/// @param minshell stores env variable
/// @return returns the position of next cgar after the end of var name
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

/// @brief Function joining everything that doesnt need expansion
/// @param i start position of the str
/// @param str string 
/// @param strlen length of the string
/// @param ret ------
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

static char	*initial_expansion(char *str, int *i, int strlen)
{
	while ((*i) < strlen && str[(*i)] != '$')
		(*i)++ ;
	if ((*i) == strlen)
		return (ft_strndup(str, (*i)));
	return (ft_strndup(str, (*i)));
}

/// @brief Expands the shell variable ($[VAR])
/// @param str str to be containing shell var 
/// @param strlen length of the string passed
/// @param minishell init struct that stores shell env that
///					contains the vars values
/// @return retuns expanded string
char	*expander(char *str, int strlen, t_minishell *minishell)
{
	char	*ret;
	int		i;

	i = 0;
	ret = initial_expansion(str, &i, strlen);
	while (i < strlen)
	{
		if (ret == NULL)
			break ;
		else if (str[i] == '$' && (str[i + 1] == '\'' || str[i + 1] == '\"'))
			i++;
		else if (str[i] == '$' && str[i + 1] == '?')
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
	return (ret);
}
