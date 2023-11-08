#include "minishell.h"

void	put_args(t_cmd **cmd_table, t_lexer **lexer, t_minishell *minishell)
{
	t_cmd	*cmds;
	int		i;
	int		words;

	cmds = *cmd_table;
	i = -1;
	words = count_words(lexer);
	cmds->cmd = (char **)ft_calloc(words + 1, sizeof(char *));
	while ((*lexer) != NULL && ++i < words && (*lexer)->token != PIPE)
	{
		if ((*lexer)->token == SQUOTE)
			cmds->cmd[i] = ft_strndup((*lexer)->start, (*lexer)->strlen);
		else if ((*lexer)->token == WORD || (*lexer)->token == DQUOTE)
			cmds->cmd[i] = expander(*lexer, minishell);
		(*lexer) = (*lexer)->next;
	}
	if ((*lexer) != NULL && (*lexer)->token == PIPE)
		(*lexer) = (*lexer)->next;
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
