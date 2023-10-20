#include "minishell.h"

int main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	(void)envp;
	// executor(envp);

	setup_signals();
	// Mock shell to check if signal functions actually get called
	while (1)
	{
		char *input = readline("minishell> ");
		if (!input)
		{
			printf("Ctrl+D was pressed!\n");
			free(input);
			break;
		}
		if (input && input[0] != '\0' && input[0] != '\n')
			add_history(input);
		free(input);
	}
	return (0);
}
