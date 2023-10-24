#ifndef MINISHELL_H
# define MINISHELL_H

/* -------------------------------- Includes -------------------------------- */

# include "common.h"
# include "pipex_bonus.h"
# include <termios.h>
# include <readline/readline.h>
# include <readline/history.h>

/* -------------------------------- Typedefs -------------------------------- */

int	g_signal_received;

typedef struct s_env {
	char			*key;
	char			*value;
	char			*full_string;
	struct s_env	*next;
}	t_env;

/* --------------------------------- Signals -------------------------------- */

void	setup_signals();

/* -------------------------------- Executor -------------------------------- */
void	executor(char **env);

/* ---------------------------------- Free ---------------------------------- */
void	free_env_linked_list(t_env	*head);

/* -------------------------------- Built-ins ------------------------------- */

int		cd(t_env **head);
int		pwd();
void	env(t_env *head);
void	echo(void);
void	unset(t_env **head, const char *key);
void	builtin_exit();

/* ---------------------------------- Utils --------------------------------- */

char	*ft_strndup(const char *str, size_t n);
int		ft_strcmp(const char *s1, const char *s2);
int		export(t_env **head, char *str);
int		copy_env_to_linked_list(char **envp, t_env **head);
t_env	*find_env_key(t_env *head, char *key);
int		add_env_node(t_env **head, char *key, char *full_string, char *value);

#endif /* MINISHELL_H */