# include "minishell.h"

/*
1. Create child process 
2. 

*/

int	executor(char **env)
{
	char 		*tokens[] = {"ls", "-la", NULL};
	t_pip_bonus	*pipex;

	pipex = (t_pip_bonus *)malloc(sizeof(t_pip_bonus));

	init(pipex, 2, tokens, env);
	if (tokens[1])
		exec();
	else
		exec_builtins();
	return (0);
}

static void	exec()
{
	
}
