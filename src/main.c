#include "minishell.h"


// GPT GENERATED FUNCTIONS FOR MOCK DATA:
void    init_mock_data(t_minishell *minishell) {
	int     i, j;
	char    *cmd_table_arr[][4] = {
		{"ls", "-l", NULL},
		{"wc", "-l", NULL},
		// {"grep", "output.txt", NULL},
		// {"echo", "Hello, World!", NULL}
	};
	int num_cmd_table = sizeof(cmd_table_arr) / sizeof(cmd_table_arr[0]);

	minishell->cmd_table = malloc(sizeof(t_cmd *) * (num_cmd_table + 1));
	for (i = 0; i < num_cmd_table; i++) {
		minishell->cmd_table[i] = malloc(sizeof(t_cmd));
		minishell->cmd_table[i]->cmd = malloc(sizeof(char *) * 4);
		for (j = 0; cmd_table_arr[i][j] != NULL; j++) {
			minishell->cmd_table[i]->cmd[j] = strdup(cmd_table_arr[i][j]);
		}
		minishell->cmd_table[i]->cmd[j] = NULL;

		minishell->cmd_table[i]->deli = "|";
		minishell->cmd_table[i]->infile = "input.txt";
		minishell->cmd_table[i]->outfile = "output.txt";
		minishell->cmd_table[i]->infile_fd = 0;
		minishell->cmd_table[i]->outfile_fd = 1;
		minishell->cmd_table[i]->here_doc = false;
	}
	minishell->cmd_table[i] = NULL;
}

void    free_mock_data(t_minishell *minishell) {
	int i, j;
	for (i = 0; minishell->cmd_table[i] != NULL; i++) {
		for (j = 0; minishell->cmd_table[i]->cmd[j] != NULL; j++) {
			free(minishell->cmd_table[i]->cmd[j]);
		}
		free(minishell->cmd_table[i]->cmd);
	}
	free(minishell->cmd_table);
}

int main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	(void)envp;
	t_minishell minishell;

	copy_env_to_linked_list(envp, &minishell.head_env);
	// init_mock_data(&minishell);
	// executor(&minishell);

	free_env_linked_list(minishell.head_env);
	// free_mock_data(&minishell);
	printf("Finished!\n");
	// t_lexer	*lexer;
	// // executor(envp);

	// setup_signals();
	// // Mock shell to check if signal functions actually get called
	// while (1)
	// {
	// 	char *input = readline("minishell> ");
	// 	if (!input)
	// 	{
	// 		printf("Ctrl+D was pressed!\n");
	// 		print_list(&lexer);
	// 		lst_del(&lexer);
	// 		free(input);
	// 		break;
	// 	}
	// 	lexer = tokenise(input);
	// 	//if (lexer == NULL)
	// 	//{
	// 	//	printf("Invalid input\n");
	// 	//	//continue ;
	// 	//}
	// 	if (input && input[0] != '\0' && input[0] != '\n')
	// 		add_history(input);
	// 	print_list(&lexer);
	// 	lst_del(&lexer);
	// 	free(input);
	// }
				
	//lexer = tokenise("ls>filename");
	//if (lexer != NULL)
	//{
	//	print_list(&lexer);
	//	lst_del(&lexer);
	//}
	return (0);
}
