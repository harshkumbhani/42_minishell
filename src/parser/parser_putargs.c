
#include "minishell.h"

static void	join_and_advance(t_lexer **lexer, char **cmd, t_minishell *minishell)
{
	char	*tmp;

	tmp = NULL;
	while (1)
	{
		if ((*lexer)->token == SQUOTE && (*lexer)->strlen > 0)
			tmp = ft_strndup((*lexer)->start, (*lexer)->strlen);
		else if (t_check((*lexer)->token) == TRUE)
			tmp = expander(*lexer, minishell);
		(*cmd) = ft_strjoin_gnl((*cmd), tmp);
		free(tmp);
		if ((*lexer)->not_space != TRUE)
			break ;
		move_and_free(lexer);
	}
}


static void ft_redir_lst(t_lexer **lexer, t_minishell *mini, int ftype, t_redir **head)
{
	t_redir	*new;

	move_and_free(lexer);
	new = ft_calloc(1, sizeof(t_redir));
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
	(void)mini;

	tmp = NULL;
	move_and_free(lexer);
	new = ft_calloc(1, sizeof(t_heredoc));
	new->expand = TRUE;
	while (1)
	{
		tmp = ft_strndup((*lexer)->start, (*lexer)->strlen);
		new->str = ft_strjoin_gnl(new->str, tmp);
		free(tmp);
		if ((*lexer)->token == SQUOTE || (*lexer)->token == DQUOTE)
			new->expand = FALSE;
		if ((*lexer)->not_space == FALSE)
			break;
		move_and_free(lexer);
	}
	hd_add_back(head, new);
	return ;
}

static void	handle_redirection(t_lexer **lexer, t_minishell *minishell, t_redir **head, t_heredoc **hd)
{
	if ((*lexer)->token == GREATER && t_check((*lexer)->next->token) == TRUE)
		ft_redir_lst(lexer, minishell, TRUNC, head);
	else if ((*lexer)->token == LESS && t_check((*lexer)->next->token) == TRUE)
		ft_redir_lst(lexer, minishell, OPEN, head);
	else if ((*lexer)->token == DOUBLE_GREATER && t_check((*lexer)->next->token) == TRUE)
		ft_redir_lst(lexer, minishell, APPEND, head);
	else if ((*lexer)->token == DOUBLE_LESS && t_check((*lexer)->next->token) == TRUE)
		ft_heredoc_lst(lexer, minishell, hd);
}

void	put_args(t_cmd **cmd_table, t_lexer **lexer, t_minishell *minishell)
{
	t_cmd	*cmds;
	int		i;
	int		j;
	int		words;

	cmds = *cmd_table;
	i = -1;
	j = -1;
	words = count_words(lexer);
	cmds->cmd = (char **)ft_calloc(words + 1, sizeof(char *));
	while ((*lexer) != NULL && ++i < words && (*lexer)->token != PIPE)
	{
		if ((*lexer)->not_space == TRUE)
			join_and_advance(lexer, &cmds->cmd[++j], minishell);
		else if ((*lexer)->token == SQUOTE && (*lexer)->strlen > 0)
			cmds->cmd[++j] = ft_strndup((*lexer)->start, (*lexer)->strlen);
		else if (((*lexer)->token == WORD || (*lexer)->token == DQUOTE) && (*lexer)->strlen > 0)
			cmds->cmd[++j] = expander(*lexer, minishell);
		else if ((*lexer)->token == LESS || (*lexer)->token == GREATER
			|| (*lexer)->token == DOUBLE_GREATER || (*lexer)->token == DOUBLE_LESS)
			handle_redirection(lexer, minishell, &cmds->files, &cmds->heredoc);
		move_and_free(lexer);
	}
	if ((*lexer) != NULL && (*lexer)->token == PIPE)
		move_and_free(lexer);
}
