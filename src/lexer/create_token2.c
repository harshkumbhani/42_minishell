#include "minishell.h"

int	create_less(t_lexer **head, char *str)
{
	t_lexer	*new;

	new = ft_calloc(1, sizeof(t_lexer));
	new->start = str;
	new->token = LESS;
	new->strlen = 1;
	lst_add_back(head, new);
	return (new->strlen);
}

int	create_greater(t_lexer **head, char *str)
{
	t_lexer	*new;

	new = ft_calloc(1, sizeof(t_lexer));
	new->start = str;
	new->token = GREATER;
	new->strlen = 1;
	lst_add_back(head, new);
	return (new->strlen);
}

int	create_dbless(t_lexer **head, char *str)
{
	t_lexer	*new;

	new = ft_calloc(1, sizeof(t_lexer));
	new->start = str;
	new->token = DOUBLE_LESS;
	new->strlen = 2;
	lst_add_back(head, new);
	return (new->strlen);
}

int	create_dbgreater(t_lexer **head, char *str)
{
	t_lexer	*new;

	new = ft_calloc(1, sizeof(t_lexer));
	new->start = str;
	new->token = DOUBLE_GREATER;
	new->strlen = 2;
	lst_add_back(head, new);
	return (new->strlen);
}
