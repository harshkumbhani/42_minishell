/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwenz <cwenz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 17:16:21 by cwenz             #+#    #+#             */
/*   Updated: 2023/11/25 17:23:26 by cwenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*strjoin_pipex(char *s1, char *s2)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	j = -1;
	if (s1 == NULL && s2 == NULL)
		return (NULL);
	str = ft_calloc(ft_strlen(s1) + ft_strlen(s2) + 1, sizeof(char));
	if (str == NULL)
		return (NULL);
	while (s1 != NULL && s1[i] != '\0')
	{
		str[i] = s1[i];
		i++;
	}
	while (s2 != NULL && s2[++j] != '\0')
		str[i + j] = s2[j];
	return (str);
}

/// @brief Adds the given pid to the linked list
/// @param minishell The struct which holds the shell info
/// @param pid The pid to add to the linked list
void	add_pid(t_minishell *minishell, int pid)
{
	t_pids	*temp;
	t_pids	*new_pid;

	temp = minishell->pids;
	new_pid = ft_calloc(1, sizeof(t_pids));
	new_pid->pid = pid;
	new_pid->has_checked = false;
	new_pid->next = NULL;
	if (!temp)
		minishell->pids = new_pid;
	else
	{
		while (temp->next)
			temp = temp->next;
		temp->next = new_pid;
	}
}

/// @brief Finds the given pid in the linked list
/// @param minishell The struct containing the pids
/// @param pid The pid to find
/// @return The pid (if found), otherwise NULL
t_pids	*find_pid(t_minishell *minishell, int pid)
{
	t_pids	*temp;

	temp = minishell->pids;
	while (temp)
	{
		if (pid == temp->pid)
			return (temp);
		temp = temp->next;
	}
	return (NULL);
}

/// @brief Loops through the linked list of pids and frees it
/// @param minishell The struct containing the linked list fo pids
void	free_pids(t_minishell *minishell)
{
	t_pids	*temp;
	t_pids	*next;

	temp = minishell->pids;
	while (temp)
	{
		next = temp->next;
		free(temp);
		temp = next;
	}
}
