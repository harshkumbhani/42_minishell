/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkumbhan <hkumbhan@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 11:31:34 by hkumbhan          #+#    #+#             */
/*   Updated: 2023/11/26 11:31:36 by hkumbhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_redir_list(t_redir **redir)
{
	t_redir	*tail;

	tail = NULL;
	while (*redir != NULL)
	{
		tail = (*redir);
		if ((*redir)->file_name != NULL)
			free((*redir)->file_name);
		if ((*redir)->file_fd != -1)
			close((*redir)->file_fd);
		(*redir) = (*redir)->next;
		free(tail);
	}
	return ;
}

void	free_heredoc(t_heredoc **heredoc)
{
	t_heredoc	*tmp;

	tmp = NULL;
	while (*heredoc != NULL)
	{
		tmp = (*heredoc);
		if ((*heredoc)->str != NULL)
			free((*heredoc)->str);
		(*heredoc) = (*heredoc)->next;
		free(tmp);
	}
	return ;
}

void	free_cmd_table(t_cmd **cmd_table)
{
	int	i;

	i = -1;
	while (cmd_table[++i] != NULL)
	{
		if (cmd_table[i] == NULL)
			return ;
		if (cmd_table[i]->cmd != NULL)
			free_arr(cmd_table[i]->cmd);
		if (cmd_table[i]->heredoc != NULL)
			free_heredoc(&cmd_table[i]->heredoc);
		if (cmd_table[i]->files != NULL)
			free_redir_list(&cmd_table[i]->files);
		free(cmd_table[i]);
		cmd_table[i] = NULL;
	}
	free(cmd_table);
}

void	move_and_free(t_lexer **lexer)
{
	t_lexer	*current;

	current = *lexer;
	(*lexer) = (*lexer)->next;
	free(current);
	current = NULL;
	return ;
}
