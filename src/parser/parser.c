#include "minishell.h"

void	handle_redirection(t_cmd *cmds, t_lexer **lexer)
{
	if ((*lexer)->token == GREATER && (*lexer)->next->token == WORD)
	{
		(*lexer) = (*lexer)->next;
		cmds->outfile = ft_strndup((*lexer)->start, (*lexer)->strlen);
		cmds->file_type = TRUNC;
	}
	else if ((*lexer)->token == LESS && (*lexer)->next->token == WORD)
	{
		(*lexer) = (*lexer)->next;
		cmds->infile = ft_strndup((*lexer)->start, (*lexer)->strlen);
		cmds->file_type = OPEN;
	}
	else if ((*lexer)->token == DOUBLE_GREATER && (*lexer)->next->token == WORD)
	{
		(*lexer) = (*lexer)->next;
		cmds->outfile = ft_strndup((*lexer)->start, (*lexer)->strlen);
		cmds->file_type = APPEND;
	}
	else if ((*lexer)->token == DOUBLE_LESS && (*lexer)->next->token == WORD)
	{
		(*lexer) = (*lexer)->next;
		cmds->deli = ft_strndup((*lexer)->start, (*lexer)->strlen);
		cmds->here_doc = TRUE;
	}
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
		if ((*lexer)->token == SQUOTE)
			cmds->cmd[++j] = ft_strndup((*lexer)->start, (*lexer)->strlen);
		else if ((*lexer)->token == WORD || (*lexer)->token == DQUOTE)
			cmds->cmd[++j] = expander(*lexer, minishell);
		else if ((*lexer)->token == LESS || (*lexer)->token == GREATER
			|| (*lexer)->token == DOUBLE_GREATER || (*lexer)->token == DOUBLE_LESS)
			handle_redirection(cmds, lexer);
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
		return (EXIT_SUCCESS);
	minishell->cmd_table = (t_cmd **)ft_calloc(i + 2, sizeof(t_cmd *));
	while (j <= i)
	{
		minishell->cmd_table[j] = ft_calloc(1, sizeof(t_cmd));
		init_t_cmd(&(minishell->cmd_table[j]));
		put_args(&(minishell)->cmd_table[j], lexer, minishell);
		print_cmd_table(&(minishell)->cmd_table[j]);
		j++;
	}
	minishell->cmd_table[j] = NULL;
	free_cmd_table(minishell->cmd_table);
	return (SUCCESS);
}
