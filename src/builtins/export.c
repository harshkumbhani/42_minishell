/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwenz <cwenz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 16:39:26 by cwenz             #+#    #+#             */
/*   Updated: 2023/11/25 15:04:46 by cwenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_key_valid(char *str);
static char	*get_key(char *str);
static void	free_strings(char *key, char *value, char *full_string);

/// @brief Executes the export command with the provided arguments
/// 
/// The function adds new env variables or modifies exiting env variables.
/// If no arguments are provided, it prints the env list sorted by ascii.
/// @param head A pointer to the head env node
/// @param str An array of strings representing the env variables to add
/// @return EXIT_SUCCESS after execution
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

/// @brief Processes a string to add/modify the env list
/// 
/// This function splits the strings into: key, value and full string.
/// @param head A pointer to the head env node
/// @param str The string to process.
void	process_string(t_env **head, char *str)
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

/// @brief Frees the allocated memory for key, value and full_string.
/// @param key A pointer to the allocated memory for key
/// @param value A pointer to the allocated memory for value
/// @param full_string A pointer to the allocated memory for full string
static void	free_strings(char *key, char *value, char *full_string)
{
	if (key)
		free(key);
	if (value)
		free(value);
	if (full_string)
		free(full_string);
}

/// @brief Checks if the given str has a valid key
/// @param str The string to check
/// @return TRUE if the key is valid, else FALSE
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

/// @brief Finds the key in a given string
/// @param str The string to extract the key from
/// @return The key if found, otherwise NULL 
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
