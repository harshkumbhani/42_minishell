#include "minishell.h"

int	parser(t_lexer **lexer, t_minishell *minishell)
{
	int		i;
	int		j;

	j = 0;
	if (*lexer == NULL)
		return (FAIL);
	if (syntax_checker(lexer) == FAIL)
		return (FAIL);
	i = count_pipes(lexer);
	minishell->cmd_table = (t_cmd **)ft_calloc(i + 2, sizeof(t_cmd *));
	if (minishell->cmd_table == NULL)
		error_handler(strerror(errno), T_LEX, NULL, lexer);
	while (j <= i)
	{
		minishell->cmd_table[j] = ft_calloc(1, sizeof(t_cmd));
		if (minishell->cmd_table[j] == NULL)
			error_handler(strerror(errno), T_LEX | T_MINI, minishell, lexer);
		init_t_cmd(&(minishell->cmd_table[j]));
		put_args(&(minishell)->cmd_table[j], lexer, minishell);
		j++;
	}
	minishell->cmd_table[j] = NULL;
	return (SUCCESS);
}
