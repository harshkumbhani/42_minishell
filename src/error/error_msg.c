/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwenz <cwenz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 16:51:45 by cwenz             #+#    #+#             */
/*   Updated: 2023/11/12 17:18:31 by cwenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

void	error_msg(char *cmd, char *reason)
{
	if (cmd && reason)
		ft_fprintf(STDERR_FILENO, "minishell: %s: %s\n", cmd, reason);
}
