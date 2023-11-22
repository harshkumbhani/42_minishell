#include "minishell.h"

static void	redirect_from_file(t_redir *redir, bool is_outfile);
static int	open_file_with_mode(char *file, int file_type);
static t_redir	*find_last_infile(t_redir *head);

void	execute_redir(t_cmd *cmds)
{
	t_redir	*temp;
	t_redir	*last_infile;

	temp = cmds->files;
	last_infile = find_last_infile(cmds->files);
	if (last_infile)
		redirect_from_file(last_infile, false);
	while (temp)
	{
		if (temp->file_type == 1 || temp->file_type == 2)
			redirect_from_file(temp, true);
		temp = temp->next;
	}
}

static void	redirect_from_file(t_redir *redir, bool is_outfile)
{
	redir->file_fd = open_file_with_mode(redir->file_name, redir->file_type);
	if (is_outfile)
		dup2(redir->file_fd, STDOUT_FILENO);
	else
		dup2(redir->file_fd, STDIN_FILENO);
	close(redir->file_fd);
}

static int	open_file_with_mode(char *file, int file_type)
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
		exit(1);
	}
	return (fd);
}

static t_redir	*find_last_infile(t_redir *head)
{
	t_redir	*temp;
	t_redir	*infile_node;

	temp = head;
	infile_node	= NULL;
	while (temp)
	{
		if (temp->file_type == 0)
			infile_node = temp;
		temp = temp->next;
	}
	return (infile_node);
}
