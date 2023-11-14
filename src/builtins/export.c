/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwenz <cwenz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 16:39:26 by cwenz             #+#    #+#             */
/*   Updated: 2023/11/14 13:52:33 by cwenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	process_string(t_env **head, char *str);
static bool	is_key_valid(char *str);
static char	*get_key(char *str);
static void	free_strings(char *key, char *value, char *full_string);

int	export(t_env **head, char **str)
{
	int	i;

	i = 0;
	if (!str[0])
	{
		print_env_ascending(*head);
		return (EXIT_SUCCESS);
	}
	while (str[i])
	{
		if (!is_key_valid(str[i]))
			error_msg("export", str[i], IDENTIFIER);
		else
			process_string(head, str[i]);
		i++;
	}
	return (EXIT_SUCCESS);
}

static void	process_string(t_env **head, char *str)
{
	char	*key;
	char	*equal_sign;
	char	*full_string;
	char	*value;

	full_string = ft_strdup(str);
	equal_sign = ft_strchr(full_string, '=');
	if (equal_sign)
	{
		key = ft_strndup(full_string, equal_sign - full_string);
		value = ft_strdup(equal_sign + 1);
		remove_key(key, head);
		if (!key || !value)
			return (free_strings(key, value, full_string));
	}
	else
	{
		key = strdup(full_string);
		full_string = ft_strjoin_gnl(full_string, "=");
		value = NULL;
		if (!key || !full_string)
			return (free_strings(key, NULL, full_string));
	}
	add_env_node(head, key, full_string, value);
}

static void	free_strings(char *key, char *value, char *full_string)
{
	if (key)
		free(key);
	if (value)
		free(value);
	if (full_string)
		free(full_string);
}

static bool	is_key_valid(char *str)
{
	int		i;
	char	*key;

	key = get_key(str);
	if (!key)
		return (false);
	if (!ft_isalpha(key[0]) && key[0] != '_')
		return (free(key), false);
	i = 1;
	while (key[i])
	{
		if (ft_isalnum(key[i]) == 0 && key[i] != '_')
			return (free(key), false);
		i++;
	}
	return (free(key), true);
}

static char	*get_key(char *str)
{
	char	*key;
	char	*equal_sign;
	char	*full_string;

	full_string = ft_strdup(str);
	if (!full_string)
		return (NULL);
	equal_sign = ft_strchr(full_string, '=');
	if (!equal_sign)
		return (full_string);
	key = ft_strndup(full_string, equal_sign - full_string);
	free(full_string);
	if (!key)
		return (NULL);
	return (key);
}
