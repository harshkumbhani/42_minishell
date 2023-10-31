
#include "minishell.h"

static int	open_file(char *file, int i);

void    open_infile(t_cmd *cmd)
{
    cmd->infile_fd = open_file(cmd->infile, 0);
    if (cmd->infile_fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }
    if (dup2(cmd->infile_fd, STDIN_FILENO) == -1) {
        perror("dup2");
        exit(EXIT_FAILURE);
    }
    close(cmd->infile_fd);
}


void	open_outfile(t_cmd *cmd)
{
	cmd->outfile_fd = open_file(cmd->outfile, 1);
	dup2(cmd->outfile_fd, STDOUT_FILENO);
	close(cmd->outfile_fd);
}

void	handle_here_doc(t_cmd *cmd)
{
	(void)cmd;
}

static int	open_file(char *file, int i)
{
	int	fd;

	fd = 0;
	if (i == 0)
		fd = open(file, O_RDONLY);
	else if (i == 1)
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (i == 2)
		fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		perror("open");
		exit(EXIT_FAILURE);
	}
	return (fd);
}
