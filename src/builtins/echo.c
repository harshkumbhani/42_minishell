/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwenz <cwenz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 09:56:50 by cwenz             #+#    #+#             */
/*   Updated: 2023/10/23 13:29:30 by cwenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


// TODO: Pass down command table to it and store exit code:
void	echo(void)
{
	bool has_n_flag = true; // placeholder for now, change this.
	bool no_string = true; // placeholder for now, change this.
	if (no_string)
		printf("\n");
	else if (has_n_flag)
		printf("PRINT STRING HERE");
	else
		printf("PRINT STRING HERE\n");
}
