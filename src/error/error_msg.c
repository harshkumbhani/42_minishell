/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwenz <cwenz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 16:51:45 by cwenz             #+#    #+#             */
/*   Updated: 2023/11/20 14:07:53 by cwenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

void	error_msg(char *cmd, char *cmd2, char *reason)
{
	if (cmd && reason && cmd2)
		ft_fprintf(STDERR_FILENO, "\033[0;31m(!)\033[0m minishell: %s: %s: %s\n", cmd, cmd2, reason);
	else if (cmd && reason)
		ft_fprintf(STDERR_FILENO, "\033[0;31m(!)\033[0m minishell: %s: %s\n", cmd, reason);
}
