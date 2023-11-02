#ifndef MINISHELL_H
# define MINISHELL_H

/* -------------------------------- Includes -------------------------------- */

# include "common.h"
// # include "pipex_bonus.h"
# include <termios.h>
# include <readline/readline.h>
# include <readline/history.h>

# define MINISHELL "Minishell"

/* -------------------------------- Typedefs -------------------------------- */

typedef enum e_token
{
	WORD			= 0,
	PIPE			= 1,
	SQUOTE			= 2,
	DQUOTE			= 3,
	BACKSLASH		= 4,
	LESS			= 5,
	GREATER			= 6,
	DOUBLE_LESS 	= 7,
	DOUBLE_GREATER	= 8
}	t_token;

typedef struct s_lexer
{
	char			*start;
	t_token			token;
	int				strlen;
	bool			space_flag;
	struct s_lexer	*next;
}	t_lexer;

typedef struct s_env {
	char			*key;
	char			*value;
	char			*full_string;
	struct s_env	*next;
}	t_env;

typedef struct s_cmd {
	char	**cmd;
	char	*deli;
	char	*infile;
	char	*outfile;
	int		infile_fd;
	int		outfile_fd;
	int		fd[2];
	bool	here_doc;
}	t_cmd;

typedef struct s_minishell {
	t_cmd	**cmd_table;
	int		exit_code;
	t_env	*head_env;
}	t_minishell;

/* --------------------------------- Lexer -------------------------------- */

t_lexer	*tokenise(char *input);

int		token_word(t_lexer **head, char *str);
int		token_pipe(t_lexer **head, char *str);
int		token_squote(t_lexer **head, char *str);
int		token_dquote(t_lexer **head, char *str);
int		token_backslash(t_lexer **head, char *str);
int		create_less(t_lexer **head, char *str);
int		create_greater(t_lexer **head, char *str);
int		create_dbless(t_lexer **head, char *str);
int		create_dbgreater(t_lexer **head, char *str);

/* --------------------------------- Signals -------------------------------- */

void	setup_signals();

/* -------------------------------- Executor -------------------------------- */

void	executor(t_minishell *minishell);
void	execute_cmd(t_cmd *cmds, t_env *head_env);
void	execute_child(t_minishell *minishell, int index);
void	execute_last_child(t_minishell *minishell, int index);
void	get_exit_status(t_minishell *minishell, int	pid);

/* ---------------------------------- Free ---------------------------------- */

void	free_env_linked_list(t_env	*head);
void	free_env_node(t_env *node);
void	free_env_array(char **envp);

/* -------------------------------- Built-ins ------------------------------- */

int		cd(t_env **head, char *path);
int		pwd(void);
int		env(t_env *head);
int		echo(char **cmd);
int		export(t_env **head, char *str);
int		unset(t_env **head, const char *key);
void	builtin_exit();
void	exec_builtins(t_minishell *minishell, int i);
bool	is_cmd_builtin(t_minishell *minishell, int i);

/* ---------------------------------- Error --------------------------------- */

void	print_error_msg(char **cmd);

/* ---------------------------------- Utils --------------------------------- */

char	*ft_strndup(const char *str, size_t n);
int		ft_strcmp(const char *s1, const char *s2);
char	*strjoin_pipex(char *s1, char *s2);

/* -------------------------------- Env Utils ------------------------------- */

int		copy_env_to_linked_list(char **envp, t_env **head);
t_env	*find_env_key(t_env *head, char *key);
int		add_env_node(t_env **head, char *key, char *full_string, char *value);
int		count_env_variables(t_env *head);

/* ------------------------------- File Utils ------------------------------- */

void	open_outfile(t_cmd *cmd);
void	open_infile(t_cmd *cmd);

/* -------------------------------- Lst-utils ------------------------------- */

void	lst_add_back(t_lexer **head, t_lexer *new_node);
void	lst_del(t_lexer **head);
void	print_list(t_lexer **head);

#endif /* MINISHELL_H */