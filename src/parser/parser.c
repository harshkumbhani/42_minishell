#include "minishell.h"

void	put_args(t_cmd **cmd_table, t_lexer **lexer, t_env **envp)
{
	t_cmd	*cmds;
	t_lexer	*lex;
	int		i;
	int		words;
	(void)envp;
	cmds = *cmd_table;
	lex = *lexer;
	i = 0;
	words = count_words(lexer);
	cmds->cmd = (char **)ft_calloc(words + 1, sizeof(char *));
	while (lex != NULL && i < words)
	{
		if (lex->token == SQUOTE)
			cmds->cmd[i] = ft_strndup(lex->start, lex->strlen);
		else if (lex->token == WORD)
			cmds->cmd[i] = ft_strndup(lex->start, lex->strlen);
		// else if (lex->token == DQUOTE)
		// 	cmds->cmd[i] = expander(lex, envp);
		lex = lex->next;
		i++;
	}
	cmds->cmd[i] = NULL;
	for(int k = 0; k < words; k++)
		printf("cmd[%d]: %s\n", k, cmds->cmd[k]);
}

int	parser(t_lexer **lexer, t_minishell *minishell)
{
	int		i;
	int		j;

	j = 0;
	i = count_pipes(lexer);
	if (lexer == NULL && *lexer == NULL)
		return (EXIT_SUCCESS);
	minishell->cmd_table = (t_cmd **)ft_calloc(i + 2, sizeof(t_cmd *));
	while (j <= i)
	{
		minishell->cmd_table[j] = ft_calloc(1, sizeof(t_cmd));
		init_t_cmd(&(minishell->cmd_table[j]));
		put_args(&(minishell)->cmd_table[j], lexer, &(minishell)->head_env);
		j++;
	}
	free_cmd_table(minishell->cmd_table);
	return (0);
}
