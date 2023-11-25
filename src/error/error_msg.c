/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkumbhan <hkumbhan@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 16:51:45 by cwenz             #+#    #+#             */
/*   Updated: 2023/11/25 14:44:33 by hkumbhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_minishell(t_minishell *minishell);

void	error_msg(char *cmd, char *cmd2, char *reason)
{
	if (cmd && reason && cmd2)
		ft_fprintf(2, "\033[0;31m(!)\033[0m minishell: %s: %s: %s\n",
			cmd, cmd2, reason);
	else if (cmd && reason)
		ft_fprintf(2, "\033[0;31m(!)\033[0m minishell: %s: %s\n", cmd, reason);
}

void	error_handler(char *str, int dst, t_minishell *mini, t_lexer **lexer)
{
	ft_fprintf(STDERR_FILENO, "\033[0;31m(!)\033[0m minishell: %s\n", str);
	if (dst & T_MINI)
		free_minishell(mini);
	if (dst & T_LEX)
		free_lexer(lexer);
	//set_exit_code(EXIT_FAILURE);
	exit(EXIT_FAILURE);
}

void	free_minishell(t_minishell *minishell)
{
	if (minishell->cmd_table != NULL && *(minishell->cmd_table) != NULL)
		free_cmd_table(minishell->cmd_table);
	if (minishell->pids != NULL)
		free_pids(minishell);
	if (minishell->head_env != NULL)
		free_env_linked_list(minishell->head_env);
}
