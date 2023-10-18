/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkumbhan <hkumbhan@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 16:28:03 by cwenz             #+#    #+#             */
/*   Updated: 2023/10/18 09:39:16 by hkumbhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>

int	main(void)
{
	char	*str;

	while (1)
	{
		str = readline(NULL);
		if (str == NULL)
			break ;
		if (history_tok)
		add_history(str);
		free(str);
	}
	return (EXIT_SUCCESS);
}
