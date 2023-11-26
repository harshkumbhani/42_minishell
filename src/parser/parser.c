/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwenz <cwenz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 11:31:50 by hkumbhan          #+#    #+#             */
/*   Updated: 2023/11/26 15:12:48 by cwenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	put_args(t_cmd **cmd_table, t_lexer **lexer, t_minishell *minishell)
{
	t_cmd	*cmds;
	int		i;
	int		j;
	int		words;

	cmds = *cmd_table;
	i = -1;
	j = -1;
	words = count_words(lexer);
	cmds->cmd = (char **)ft_calloc(words + 1, sizeof(char *));
	while ((*lexer) != NULL && ++i < words && (*lexer)->token != PIPE)
	{
		add_arg(cmds, lexer, minishell, &j);
		move_and_free(lexer);
	}
	i = -1;
	while (cmd_table[++i] != NULL)
	{
		if (cmd_table[i]->cmd == NULL && cmd_table[i]->files == NULL
			&& cmd_table[i]->heredoc == NULL)
			error_handler(strerror(errno), T_LEX | T_MINI, minishell, lexer);
	}
	if ((*lexer) != NULL && (*lexer)->token == PIPE)
		move_and_free(lexer);
}

int	parser(t_lexer **lexer, t_minishell *minishell)
{
	int		i;
	int		j;

	j = 0;
	if (*lexer == NULL)
		return (FAIL);
	if (syntax_checker(lexer) == FAIL)
		return (FAIL);
	i = count_pipes(lexer);
	minishell->cmd_table = (t_cmd **)ft_calloc(i + 2, sizeof(t_cmd *));
	if (minishell->cmd_table == NULL)
		error_handler(strerror(errno), T_LEX, NULL, lexer);
	while (j <= i)
	{
		minishell->cmd_table[j] = ft_calloc(1, sizeof(t_cmd));
		if (minishell->cmd_table[j] == NULL)
			error_handler(strerror(errno), T_LEX | T_MINI, minishell, lexer);
		init_t_cmd(&(minishell->cmd_table[j]));
		put_args(&(minishell)->cmd_table[j], lexer, minishell);
		// print_cmd_table(minishell->cmd_table);
		j++;
	}
	minishell->cmd_table[j] = NULL;
	return (SUCCESS);
}
