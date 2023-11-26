/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwenz <cwenz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 18:30:02 by cwenz             #+#    #+#             */
/*   Updated: 2023/11/26 11:14:43 by cwenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void			execute_heredoc(t_minishell *minishell, int index);
static t_heredoc	*get_last_heredoc(t_heredoc *heredoc);
static bool			execute_individual_heredoc(t_minishell *minishell,
						char *str, t_heredoc *heredoc);

/// @brief Executes a heredoc command.
///
/// The function sets up a `pipe`, `forks` a child process to handle heredoc
/// input. In the child it executes the heredoc logic. In the parent it closes
/// the write-end of the pipe and duplicates the read-end to standard input.
/// It then waits for the child process to end.
/// @param minishell 
/// @param index 
void	handle_heredoc(t_minishell *minishell, int index)
{
	int		pid;
	t_pids	*pid_node;

	if (pipe(minishell->fd) == -1)
		error_handler(strerror(errno), T_MINI, minishell, NULL);
	block_signal();
	pid = fork();
	if (pid == -1)
		error_handler(strerror(errno), T_MINI, minishell, NULL);
	if (pid == 0)
	{
		setup_heredoc_signals();
		execute_heredoc(minishell, index);
	}
	else
	{
		add_pid(minishell, pid);
		close(minishell->fd[1]);
		dup2(minishell->fd[0], STDIN_FILENO);
		close(minishell->fd[0]);
		pid_node = find_pid(minishell, pid);
		pid_node->has_checked = true;
		get_exit_status(pid);
	}
}

/// @brief Executes the heredoc reading process for the command.
///
/// It loops until each heredoc's deliminator is reached. The read
/// content is sent to the read-end of the pipe.
/// @param minishell The struct containing the shell information.
/// @param index The current index of the command table to execute.
static void	execute_heredoc(t_minishell *minishell, int index)
{
	char		*str;
	t_heredoc	*temp;

	temp = minishell->cmd_table[index]->heredoc;
	close(minishell->fd[0]);
	while (temp)
	{
		while (true)
		{
			str = readline("> ");
			if (!str)
				break ;
			if (!execute_individual_heredoc(minishell, str, temp))
				break ;
			free(str);
		}
		temp = temp->next;
	}
	close(minishell->fd[1]);
	exit(0);
}

/// @brief Gets the last heredoc command in the linked list.
/// @param heredoc The head node of the heredoc linked list
/// @return The last heredoc command. 
static t_heredoc	*get_last_heredoc(t_heredoc *heredoc)
{
	while (heredoc->next)
		heredoc = heredoc->next;
	return (heredoc);
}

/// @brief Executes an individual heredoc within the loop.
///
/// The function checks whether it should exit the loop or not, based
/// on the heredoc deliminator. If the given heredoc is the last heredoc it
/// writes to the pipe.
/// @param minishell The struct containing shell information
/// @param str The str thats read from the command line
/// @param heredoc The current heredoc
/// @return TRUE if the process should continue, otherwise FALSE.
static bool	execute_individual_heredoc(t_minishell *minishell,
				char *str, t_heredoc *heredoc)
{
	t_heredoc	*last_heredoc;

	last_heredoc = get_last_heredoc(heredoc);
	if (ft_strcmp(heredoc->str, str) == 0)
	{
		free(str);
		return (false);
	}
	if (last_heredoc == heredoc)
	{
		if (heredoc->expand)
			str = expander(str, ft_strlen(str), minishell);
		write(minishell->fd[1], str, ft_strlen(str));
		write(minishell->fd[1], "\n", 1);
	}
	return (true);
}
