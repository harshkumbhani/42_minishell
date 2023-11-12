
#include "minishell.h"

static void	run_minishell(t_minishell *minishell);

int main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	t_minishell	minishell;

	minishell = (t_minishell){};
	copy_std_fds(&minishell);
	export(&minishell.head_env, envp);
	setup_signals();
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
		input = readline("minishell> ");
		if (!input)
		{
			printf("Ctrl+D was pressed!\n");
			lst_del(&lexer);
			break ;
		}
		if (input && input[0] != '\0' && input[0] != '\n')
			add_history(input);
		lexer = tokenise(input);
		if (parser(&lexer, minishell) == FAIL)
		{
			lst_del(&lexer);
			continue ;
		}
		executor(minishell);
		free(input);
		lst_del(&lexer);
		free_cmd_table(minishell->cmd_table);
		reset_fds(minishell);
	}
}
