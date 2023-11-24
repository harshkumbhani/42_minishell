
#include "minishell.h"

char	*strjoin_pipex(char *s1, char *s2)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	j = -1;
	if (s1 == NULL && s2 == NULL)
		return (NULL);
	str = ft_calloc(ft_strlen(s1) + ft_strlen(s2) + 1, sizeof(char));
	if (str == NULL)
		return (NULL);
	while (s1 != NULL && s1[i] != '\0')
	{
		str[i] = s1[i];
		i++;
	}
	while (s2 != NULL && s2[++j] != '\0')
		str[i + j] = s2[j];
	return (str);
}

void	copy_std_fds(t_minishell *minishell)
{
	minishell->stdfds.stdin = dup(STDIN_FILENO);
	minishell->stdfds.stdout = dup(STDOUT_FILENO);
}

void	reset_fds(t_minishell *minishell)
{
	dup2(minishell->stdfds.stdin, STDIN_FILENO);
	dup2(minishell->stdfds.stdout, STDOUT_FILENO);
}

void	add_pid(t_minishell *minishell, int pid)
{
	t_pids	*temp;
	t_pids	*new_pid;

	temp = minishell->pids;
	new_pid = ft_calloc(1, sizeof(t_pids));
	new_pid->pid = pid;
	new_pid->next = NULL;
	if (!temp)
		minishell->pids = new_pid;
	else
	{
		while (temp->next)
			temp = temp->next;
		temp->next = new_pid;
	}
}

void	free_pids(t_minishell *minishell)
{
	t_pids	*temp;
	t_pids	*next;

	temp = minishell->pids;
	while (temp)
	{
		next = temp->next;
		free(temp);
		temp = next;
	}
}
