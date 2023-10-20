/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwenz <cwenz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 10:50:36 by cwenz             #+#    #+#             */
/*   Updated: 2023/10/17 10:44:11 by cwenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

/*
1. Create child process 
2. 

*/

static void	handle_no_pipes(t_pip_bonus *pipex);
static void	handle_pipes(t_pip_bonus *pipex);

void	executor(char **env)
{
	char 		*tokens[] = {"ls", "-la", NULL};
	bool		is_pipes = false;
	t_pip_bonus	*pipex;

	pipex = (t_pip_bonus *)malloc(sizeof(t_pip_bonus));

	init(pipex, 2, tokens, env);
	if (is_pipes)
		handle_pipes(pipex);
	else
		handle_no_pipes(pipex);
	(void)handle_pipes(pipex);
}

static void	handle_no_pipes(t_pip_bonus *pipex)
{
	char	*path;
	
	path = find_cmd_path(pipex, pipex->argv[0]);
	if (path == NULL)
	{
		error_bonus(ERR_CMD, pipex->argv[0], pipex);
		exit(EXIT_FAILURE);
	}
	if (execve(path, pipex->argv, pipex->envp) == -1)
	{
		free(path);
		error_bonus(ERR_CMD, pipex->argv[0], pipex);
		free_arr(pipex->argv);
		exit(EXIT_FAILURE);
	}
}

static void	handle_pipes(t_pip_bonus *pipex)
{
	(void)pipex;
}
