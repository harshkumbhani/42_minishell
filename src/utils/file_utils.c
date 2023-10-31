
#include "minishell.h"

static int	open_file(char *file, int i);

void	open_infile(t_cmd *cmd)
{
	cmd->infile_fd = open_file(cmd->infile, 0);
	dup2(cmd->infile_fd, STDIN_FILENO);
}

void	open_outfile(t_cmd *cmd)
{
	cmd->outfile_fd = open_file(cmd->outfile, 1);
	dup2(cmd->outfile_fd, STDIN_FILENO);
}

static int	open_file(char *file, int i)
{
	int	fd;

	fd = 0;
	if (i == 0)
		fd = open(file, O_RDONLY);
	else if (i == 1)
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	return (fd);
}
