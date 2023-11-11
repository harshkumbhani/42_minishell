#include "minishell.h"

// TODO: Implement SHLVL

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

int main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	(void)envp;
	t_minishell minishell;
	char		*input;
	t_lexer		*lexer;

	minishell = (t_minishell){};
	copy_std_fds(&minishell);
	export(&minishell.head_env, envp);
	setup_signals();
	while (1)
	{
		input = readline("minishell> ");
		// if (!input)
		// {
		// 	printf("Ctrl+D was pressed!\n");
		// 	lst_del(&lexer);
		// 	free(input);
		// 	break;
		// }
		lexer = tokenise(input);
		//print_list(&lexer);
		if (input && input[0] != '\0' && input[0] != '\n')
			add_history(input);
		if (parser(&lexer, &minishell) == FAIL)
		{
			lst_del(&lexer);
			continue;
		}
		// print_cmd_table(&minishell.cmd_table[0]);
		executor(&minishell);
		free_cmd_table(minishell.cmd_table);
		lst_del(&lexer);
		free(input);
		reset_fds(&minishell);
		// dup2(stdin, STDIN_FILENO);
	}
				
	// lexer = tokenise("ls -al");
	// if (lexer != NULL)
	// {
	// 	print_list(&lexer);
	// }
	// parser(&lexer, &minishell);
	// executor(&minishell);
	//lst_del(&lexer);
	free_env_linked_list(minishell.head_env);
	return (0);
}
