#include "minishell.h"

int	t_check(t_token token_type)
{
	if (token_type == WORD || token_type == DQUOTE)
		return (TRUE);
	return (FALSE);
}

static void ft_redir_lst(t_lexer **lexer, t_minishell *mini, int ftype, t_redir **head)
{
	t_redir	*new;

	new = ft_calloc(1, sizeof(t_redir));
	(*lexer) = (*lexer)->next;
	new->file_name = expander((*lexer), mini);
	new->file_type = ftype;
	new->file_fd = -1;
	redir_add_back(head, new);
	return ;
}

void	handle_redirection(t_lexer **lexer, t_minishell *minishell, t_redir **head, char **deli)
{
	static int	i = 0;

	if ((*lexer)->token == GREATER && t_check((*lexer)->next->token) == TRUE)
		ft_redir_lst(lexer, minishell, TRUNC, head);
	else if ((*lexer)->token == LESS && t_check((*lexer)->next->token) == TRUE)
		ft_redir_lst(lexer, minishell, OPEN, head);
	else if ((*lexer)->token == DOUBLE_GREATER && t_check((*lexer)->next->token) == TRUE)
		ft_redir_lst(lexer, minishell, APPEND, head);
	else if ((*lexer)->token == DOUBLE_LESS && t_check((*lexer)->next->token) == TRUE)
	{
		
	}
}

static void	join_and_advance(t_lexer **lexer, char **cmd, t_minishell *minishell)
{
	char	*tmp;
	char	*ret;

	(void)cmd;
	ret = ft_strdup("");
	tmp = NULL;
	while (1)
	{
		if ((*lexer)->token == SQUOTE && (*lexer)->strlen > 0)
			tmp = ft_strndup((*lexer)->start, (*lexer)->strlen);
		else if (t_check((*lexer)->token) == TRUE)
			tmp = expander(*lexer, minishell);
		ret = ft_strjoin(ret, tmp);
		free(tmp);
		if ((*lexer)->not_space != TRUE)
			break ;
		(*lexer) = (*lexer)->next;
	}
	*cmd = ret;
}

void	put_args(t_cmd **cmd_table, t_lexer **lexer, t_minishell *minishell)
{
	t_cmd	*cmds;
	int		i;
	int		j;
	int		words;
	t_lexer	*lex;

	cmds = *cmd_table;
	i = -1;
	j = -1;
	lex = NULL;
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
			handle_redirection(lexer, minishell, &cmds->files, cmds->deli);
		lex = (*lexer);
		(*lexer) = (*lexer)->next;
		free(lex);
	}
	if ((*lexer) != NULL && (*lexer)->token == PIPE)
	{
		lex = (*lexer);
		(*lexer) = (*lexer)->next;
		free(lex);
	}
}

int	parser(t_lexer **lexer, t_minishell *minishell)
{
	int		i;
	int		j;

	j = 0;
	if (syntax_checker(lexer, minishell) == FAIL)
		return (FAIL);
	i = count_pipes(lexer);
	if (*lexer == NULL)
		return (FAIL);
	minishell->cmd_table = (t_cmd **)ft_calloc(i + 2, sizeof(t_cmd *));
	while (j <= i)
	{
		minishell->cmd_table[j] = ft_calloc(1, sizeof(t_cmd));
		init_t_cmd(&(minishell->cmd_table[j]));
		put_args(&(minishell)->cmd_table[j], lexer, minishell);
		print_cmd_table(&minishell->cmd_table[j]);
		j++;
	}
	minishell->cmd_table[j] = NULL;
	return (SUCCESS);
}
