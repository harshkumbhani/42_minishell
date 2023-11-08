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
	printf("number of words : %d\n", i);
	return (i);
}

int	special_var(char *str, char **ret, t_minishell *minishell)
{
	(void)str;
	int		i;
	char	*tmp;

	i = 0;
	tmp = ft_itoa(minishell->exit_code);
	*ret = ft_strjoin(*ret, tmp);
	free(tmp);
	return (2);
}

char	*expander(t_lexer *lexer, t_minishell *minishell)
{
	t_env	*envp;
	char	*ret;
	char	*tmp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	ret = NULL;
	tmp = NULL;
	envp = minishell->head_env;
	while (i < lexer->strlen && lexer->start[i] != '$')
		i++ ;
	if (i == lexer->strlen)
		return (ft_strndup(lexer->start, i));
	ret = ft_strndup(lexer->start, i);
	while (i < lexer->strlen)
	{
		if (lexer->start[i] == '$' && lexer->start[i + 1] == '?')
			i += special_var(&lexer->start[i], &ret, minishell);
		else
			i++;
	}
	return (ret);
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
