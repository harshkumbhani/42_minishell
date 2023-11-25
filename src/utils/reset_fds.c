/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset_fds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwenz <cwenz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 17:22:56 by cwenz             #+#    #+#             */
/*   Updated: 2023/11/25 17:23:09 by cwenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	copy_std_fds(t_minishell *minishell)
{
	minishell->stdfds.stdin = dup(STDIN_FILENO);
	minishell->stdfds.stdout = dup(STDOUT_FILENO);
}

void	reset_fds(t_minishell *minishell)
{
	dup2(minishell->stdfds.stdin, STDIN_FILENO);
	dup2(minishell->stdfds.stdout, STDOUT_FILENO);
}
