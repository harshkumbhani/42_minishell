
#include "minishell.h"

static void	run_minishell(t_minishell *minishell);

int	main(int argc, char **argv, char **envp)
{
	t_minishell	minishell;

	(void)argv;
	if (argc != 1)
	{
		ft_putstr_fd("Run as ./minihsell with no args\n", 2);
		exit(EXIT_FAILURE);
	}
	minishell = (t_minishell){};
	copy_std_fds(&minishell);
	export(&minishell.head_env, envp);
	run_minishell(&minishell);
	free_env_linked_list(minishell.head_env);
	return (0);
}

static void	run_minishell(t_minishell *minishell)
{
	char		*input;
	t_lexer		*lexer;

	while (1)
	{
		setup_signals();
		input = readline("minishell> ");
		if (!input)
			break ;
		if (input && input[0] != '\0' && input[0] != '\n')
			add_history(input);
		lexer = tokenise(input);
		//print_list(&lexer);
		if (parser(&lexer, minishell) == FAIL)
		{
			lst_del(&lexer);
			continue ;
		}
		free(input);
		lst_del(&lexer);
		executor(minishell);
		free_cmd_table(minishell->cmd_table);
		reset_fds(minishell);
	}
}
