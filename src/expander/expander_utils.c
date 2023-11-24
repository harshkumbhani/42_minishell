/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkumbhan <hkumbhan@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 16:08:24 by hkumbhan          #+#    #+#             */
/*   Updated: 2023/11/24 18:40:47 by hkumbhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief Checks if the varaible name is valid
/// @param c first character after $
/// @return True if the char after $ is alphabet or '_'
int	check_var(char c)
{
	if (ft_isalnum(c) == TRUE || c == '_')
		return (TRUE);
	return (FALSE);
}

/// @brief Exapnds the value of $?
/// @param ret address of the return string
/// @param minishell 
/// @return returns 2 since $? is length of 2
int	special_var(char **ret, t_minishell *minishell)
{
	char	*tmp;

	tmp = ft_itoa(minishell->exit_code);
	*ret = ft_strjoin(*ret, tmp);
	free(tmp);
	return (2);
}

/// @brief Expands speacil chacrter other than ? after $
/// @param ret address of the return string
/// @param str string from lexer
/// @return returns 2
int	special_char(char **ret, char *str)
{
	char	*tmp;

	tmp = NULL;
	tmp = ft_strndup(str, 2);
	*ret = ft_strjoin_gnl(*ret, tmp);
	free(tmp);
	return (2);
}
