/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwenz <cwenz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 16:51:45 by cwenz             #+#    #+#             */
/*   Updated: 2023/11/12 16:56:31 by cwenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

void	error_msg(t_error_type error_type, char *str)
{
	if (error_type == ERR_INVALID_IDENTIFIER)
		ft_fprintf(STDERR_FILENO, "minishell: export: \'%s\': %s\n", 
			str, IDENTIFIER);
}
