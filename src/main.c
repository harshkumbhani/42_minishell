#include "minishell.h"

int main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	(void)envp;
	t_minishell	minishell;

	minishell = (t_minishell){};
	copy_env_to_linked_list(envp, &minishell.head_env);
	//env(minishell.head_env);
	//free_env_linked_list(minishell.head_env);
	t_lexer	*lexer;
	// executor(envp);

	setup_signals();
	// Mock shell to check if signal functions actually get called
	while (1)
	{
		char *input = readline("minishell> ");
		if (!input)
		{
			printf("Ctrl+D was pressed!\n");
			lst_del(&lexer);
			free(input);
			break;
		}
		lexer = tokenise(input);
		print_list(&lexer);
		parser(&lexer, &minishell);
		//if (lexer == NULL)
		//{
		//	printf("Invalid input\n");
		//	//continue ;
		//}
		if (input && input[0] != '\0' && input[0] != '\n')
			add_history(input);
		lst_del(&lexer);
		free(input);
	}
				
	// lexer = tokenise("echo '$USER'");
	// if (lexer != NULL)
	// {
	// 	print_list(&lexer);
	// }
	// parser(&lexer, &minishell);
	// lst_del(&lexer);
	free_env_linked_list(minishell.head_env);
	return (0);
}
