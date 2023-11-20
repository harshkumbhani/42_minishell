#include "minishell.h"

void	init_t_cmd(t_cmd **cmd)
{
	t_cmd	*current;

	current = *cmd;
	current->cmd = NULL;
	current->deli = NULL;
	current->files = NULL;
}

void	free_redir_list(t_redir **redir)
{
	t_redir	*tail;

	tail = NULL;
	while (*redir != NULL)
	{
		tail = (*redir);
		(*redir) = (*redir)->next;
		free(tail);
	}
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
		if (cmd_table[i]->files != NULL)
			free_redir_list(&cmd_table[i]->files);
		free(cmd_table[i]);
		cmd_table[i] = NULL;
	}
	free(cmd_table);
}

void	redir_add_back(t_redir	**head, t_redir *new_node)
{
	t_redir	*new;

	new = *head;
	if (*head == NULL)
		*head = new_node;
	else
	{
		while (new->next != NULL)
			new = new->next;
		new->next = new_node;
	}
}

void	print_files(t_redir **head)
{
	t_redir	*tmp;

	tmp = *head;
	while(tmp != NULL)
	{
		printf("File name: %s\n", tmp->file_name);
		printf("File type: %d\n", tmp->file_type);
		tmp = tmp->next;
	}
}

void	print_cmd_table(t_cmd **cmd_table)
{
	t_cmd	*tmp;
	t_redir	*redir;
	int		k;

	k = -1;
	tmp = (*cmd_table);
	redir = tmp->files;
	printf("\nCommand table: \n");
	if (tmp != NULL)
	{
		while (tmp->cmd[++k] != NULL)
			printf("cmd[%d]: %s\n", k, tmp->cmd[k]);
	}
	printf("Deli: %s\n", tmp->deli);
	print_files(&tmp->files);
}
