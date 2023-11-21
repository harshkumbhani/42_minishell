
#ifndef EXECUTOR_PROTOTYPES_H
# define EXECUTOR_PROTOTYPES_H

# include "structs.h"

void	executor(t_minishell *minishell);
void	execute_cmd(t_cmd *cmds, t_env *head_env);
void	execute_cmd_with_pipe(t_minishell *minishell, int index);
void	execute_final_cmd(t_minishell *minishell, int index);
void	get_exit_status(t_minishell *minishell);
void	handle_heredoc(t_minishell *minishell, int index);
int		handle_file_execution_errors(char *path);

#endif