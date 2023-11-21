
#include "minishell.h"

int	count_pipes(t_lexer **lexer)
{
	int		i;
	t_lexer	*current;

	i = 0;
	current = *lexer;
	if (current == NULL)
		return (i);
	while (current != NULL)
	{
		if (current->token == PIPE)
			i++;
		current = current->next;
	}
	return (i);
}

int	count_words(t_lexer **lexer)
{
	t_lexer	*lex;
	int		i;

	i = 0;
	lex = *lexer;
	while (lex != NULL && lex->token != PIPE)
	{
		if (lex->token == WORD || lex->token == SQUOTE
				|| lex->token == DQUOTE)
			i++;
		lex = lex->next;
	}
	return (i);
}

void	print_files(t_redir *head)
{
	while(head != NULL)
	{
		printf("File name: %s\n", head->file_name);
		printf("File type: %d\n", head->file_type);
		head = head->next;
	}
}

void	print_cmd_table(t_cmd **cmd_table)
{
	t_cmd		*tmp;
	t_redir		*redir;
	t_heredoc	*hd;
	int			k;

	k = -1;
	tmp = (*cmd_table);
	redir = tmp->files;
	hd = tmp->heredoc;
	printf("\nCommand table: \n");
	if (tmp != NULL)
	{
		while (tmp->cmd[++k] != NULL)
			printf("cmd[%d]: %s\n", k, tmp->cmd[k]);
	}
	while (hd != NULL)
	{
		printf("heredoc: %s\n", hd->str);
		hd = hd->next;
	}
	print_files(redir);
}