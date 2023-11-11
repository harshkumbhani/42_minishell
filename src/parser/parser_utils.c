
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

void	init_t_cmd(t_cmd **cmd)
{
	t_cmd	*current;

	current = *cmd;
	current->cmd = NULL;
	current->deli = NULL;
	current->infile = NULL;
	current->outfile = NULL;
	current->infile_fd = -1;
	current->outfile_fd = -1;
	current->file_type = -1;
	current->here_doc = FALSE;
}

void	free_cmd_table(t_cmd **cmd_table)
{
	int	i;

	i = -1;
	while (cmd_table[++i] != NULL)
	{
		if (cmd_table[i] == NULL)
			return ;
		if (cmd_table[i]->cmd != NULL)
			free_arr(cmd_table[i]->cmd);
		if (cmd_table[i]->deli != NULL)
			free(cmd_table[i]->deli);
		if (cmd_table[i]->infile != NULL)
			free(cmd_table[i]->infile);
		if (cmd_table[i]->outfile != NULL)
			free(cmd_table[i]->outfile);
		if (cmd_table[i]->infile_fd != -1)
			close(cmd_table[i]->infile_fd);
		if (cmd_table[i]->outfile_fd != -1)
			close(cmd_table[i]->outfile_fd);
		free(cmd_table[i]);
		cmd_table[i] = NULL;
	}
	free(cmd_table);
}
