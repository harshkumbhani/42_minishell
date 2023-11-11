#include "minishell.h"

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

void	print_cmd_table(t_cmd **cmd_table)
{
	t_cmd	*tmp;
	int		k;

	k = -1;
	tmp = (*cmd_table);
	printf("\nCommand table: \n");
	if (tmp != NULL)
	{
		while (tmp->cmd[++k] != NULL)
			printf("cmd[%d]: %s\n", k, tmp->cmd[k]);
	}
	printf("Deli: %s\ninfile: %s\noutfile: %s\n", tmp->deli, tmp->infile, tmp->outfile);
	printf("infile_fd: %d\noutfile_fd: %d\n", tmp->infile_fd, tmp->outfile_fd);
	printf("file_type: %d\n", tmp->file_type);
	printf("here_doc: %s\n", tmp->here_doc?"TRUE":"FALSE");
}
