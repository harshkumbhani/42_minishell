#include "minishell.h"

void	init_t_cmd(t_cmd **cmd)
{
	t_cmd	*current;

	current = *cmd;
	current->cmd = NULL;
	current->heredoc = NULL;
	current->files = NULL;
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

void	hd_add_back(t_heredoc **head, t_heredoc *new)
{
	t_heredoc	*tmp;

	tmp = *head;
	if (*head == NULL)
		(*head) = new;
	else
	{
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new;
	}
	return ;
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
		printf("Expand: %s\n", hd->expand ? "TRUE" : "FALSE");
		hd = hd->next;
	}
	print_files(redir);
}
