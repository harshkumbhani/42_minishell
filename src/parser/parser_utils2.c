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
