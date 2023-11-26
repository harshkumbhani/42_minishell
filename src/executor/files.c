/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwenz <cwenz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 18:30:05 by cwenz             #+#    #+#             */
/*   Updated: 2023/11/26 14:15:52 by cwenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		redirect_from_file(t_redir *redir, bool is_outfile, t_minishell *minishell);
static int		open_file_with_mode(char *file, int file_type,
			t_minishell *minishell);

/// @brief Executes file redirecitons for a specific command.
/// 
/// This function sets up file redirections for a command based on the
/// command redireciton. It first finds and redirects the last input file
/// (if any), and then iterates through all output file redirections.
/// @param cmds The given command that holds the file redirection information.
void	execute_redir(t_cmd *cmds, t_minishell *minishell)
{
	t_redir	*temp;

	temp = cmds->files;
	while (temp)
	{
		if (temp->file_type == 0)
			redirect_from_file(temp, false, minishell);
		if (temp->file_type == 1 || temp->file_type == 2)
			redirect_from_file(temp, true, minishell);
		temp = temp->next;
	}
}

/// @brief Redirects standard input or output to a file.
/// Opens a file and redirects either to standard out or in based on
/// `is_outfile` flag. 
/// @param redir The struct containing the file name and type.
/// @param is_outfile Boolean flag to indicate if the file is an outfile
/// (true) or and infile (false).
static void	redirect_from_file(t_redir *redir, bool is_outfile,
			t_minishell *minishell)
{
	redir->file_fd = open_file_with_mode(redir->file_name, redir->file_type, minishell);
	if (is_outfile)
		dup2(redir->file_fd, STDOUT_FILENO);
	else
		dup2(redir->file_fd, STDIN_FILENO);
	close(redir->file_fd);
}

/// @brief Opens the given file with a specific mode.
///
/// Opens a file for reading or writing based on the `file_type`.
/// The function only handles: read-only, write-only (with truncation),
/// write-only (with appending). If the file cannot be opened it displays an
/// error message and `exit(1)`.
/// @param file The file to open.
/// @param file_type The type of operation to do. 0 for read, 1 for write with
/// trunc, 2 for write with appending.
/// @return The file descriptor of the opened file
static int	open_file_with_mode(char *file, int file_type,
		t_minishell *minishell)
{
	int	fd;

	fd = 0;
	if (file_type == 0)
		fd = open(file, O_RDONLY);
	else if (file_type == 1)
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (file_type == 2)
		fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		error_msg(file, NULL, strerror(errno));
		free_cmd_table(minishell->cmd_table);
		exit(1);
	}
	return (fd);
}
