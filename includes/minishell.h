#ifndef MINISHELL_H
# define MINISHELL_H

/* -------------------------------- Includes -------------------------------- */

# include "common.h"
# include "pipex_bonus.h"
# include <termios.h>
# include <readline/readline.h>
# include <readline/history.h>

/* -------------------------------- Typedefs -------------------------------- */

typedef enum e_token
{
	WORD,
	ARG
}	t_token;

typedef struct s_lexer
{
	char			*start;
	t_token			token;
	int				strlen;
	struct s_lexer	*next;
}	t_lexer;

int	g_signal_received;

/* --------------------------------- Signals -------------------------------- */

void	setup_signals();

/* -------------------------------- Executor -------------------------------- */
int		executor(char **env);

/* -------------------------------- Built-ins ------------------------------- */

int		cd(char *path);
int		pwd();
int		env(char **env);
void	echo(char *str);

#endif /* MINISHELL_H */