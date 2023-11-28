/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_putargs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkumbhan <hkumbhan@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 11:31:24 by hkumbhan          #+#    #+#             */
/*   Updated: 2023/11/28 10:51:39 by hkumbhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	join_and_advance(t_lexer **lexer, char **cmd,
														t_minishell *minishell)
{
	char	*tmp;

	while (1)
	{
		tmp = NULL;
		if ((*lexer)->token == SQUOTE)
			tmp = ft_strndup((*lexer)->start, (*lexer)->strlen);
		else if ((*lexer)->token == WORD)
			tmp = expander((*lexer)->start, (*lexer)->strlen, minishell, WORD);
		else if ((*lexer)->token == DQUOTE)
			tmp = expander((*lexer)->start, (*lexer)->strlen, minishell,
					DQUOTE);
		if (tmp == NULL && (*lexer)->strlen > 0)
			error_handler(strerror(errno), T_LEX | T_MINI, minishell, lexer);
		(*cmd) = ft_strjoin_gnl((*cmd), tmp);
		if (tmp != NULL)
			free(tmp);
		if ((*cmd) == NULL && (*lexer)->strlen > 0)
			error_handler(strerror(errno), T_LEX | T_MINI, minishell, lexer);
		if ((*lexer)->not_space != TRUE && (*lexer)->token != PIPE)
			break ;
		move_and_free(lexer);
	}
}

static void	ft_redir_lst(t_lexer **lexer, t_minishell *mini,
												int ftype, t_redir **head)
{
	t_redir	*new;

	move_and_free(lexer);
	new = ft_calloc(1, sizeof(t_redir));
	if (new == NULL)
		error_handler(strerror(errno), T_LEX | T_MINI, mini, lexer);
	join_and_advance(lexer, &new->file_name, mini);
	new->file_type = ftype;
	new->file_fd = -1;
	redir_add_back(head, new);
	return ;
}

static void	ft_heredoc_lst(t_lexer **lexer, t_minishell *mini, t_heredoc **head)
{
	t_heredoc	*new;
	char		*tmp;

	move_and_free(lexer);
	new = ft_calloc(1, sizeof(t_heredoc));
	if (new == NULL)
		error_handler(strerror(errno), T_LEX | T_MINI, mini, lexer);
	new->expand = TRUE;
	while (1)
	{
		tmp = NULL;
		tmp = ft_strndup((*lexer)->start, (*lexer)->strlen);
		new->str = ft_strjoin_gnl(new->str, tmp);
		if ((tmp == NULL || new->str == NULL) && (*lexer)->strlen > 0)
			error_handler(strerror(errno), T_LEX | T_MINI, mini, lexer);
		if ((*lexer)->token == SQUOTE || (*lexer)->token == DQUOTE)
			new->expand = FALSE;
		if (tmp != NULL)
			free(tmp);
		if ((*lexer)->not_space == FALSE)
			break ;
		move_and_free(lexer);
	}
	hd_add_back(head, new);
	return ;
}

static void	handle_redirection(t_lexer **lexer, t_minishell *minishell,
											t_redir **head, t_heredoc **hd)
{
	if ((*lexer)->token == GREATER && t_check((*lexer)->next->token) == TRUE)
		ft_redir_lst(lexer, minishell, TRUNC, head);
	else if ((*lexer)->token == LESS && t_check((*lexer)->next->token) == TRUE)
		ft_redir_lst(lexer, minishell, OPEN, head);
	else if ((*lexer)->token == DOUBLE_GREATER
		&& t_check((*lexer)->next->token) == TRUE)
		ft_redir_lst(lexer, minishell, APPEND, head);
	else if ((*lexer)->token == DOUBLE_LESS
		&& t_check((*lexer)->next->token) == TRUE)
		ft_heredoc_lst(lexer, minishell, hd);
}

void	add_arg(t_cmd *cmds, t_lexer **lexer, t_minishell *minishell, int *j)
{
	if ((*lexer)->not_space == TRUE)
		join_and_advance(lexer, &cmds->cmd[++(*j)], minishell);
	else if ((*lexer)->token == SQUOTE)
		cmds->cmd[++(*j)] = ft_strndup((*lexer)->start, (*lexer)->strlen);
	else if ((*lexer)->token == WORD)
		cmds->cmd[++(*j)] = expander((*lexer)->start,
				(*lexer)->strlen, minishell, WORD);
	else if ((*lexer)->token == DQUOTE)
		cmds->cmd[++(*j)] = expander((*lexer)->start,
				(*lexer)->strlen, minishell, DQUOTE);
	else if (is_redirect(*lexer))
		handle_redirection(lexer, minishell, &cmds->files, &cmds->heredoc);
}
