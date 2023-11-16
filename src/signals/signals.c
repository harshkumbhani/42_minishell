/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwenz <cwenz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 12:32:52 by cwenz             #+#    #+#             */
/*   Updated: 2023/11/16 15:44:56 by cwenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

static void handle_parent_signal(int signo);
static void	setup_termios_config(void);
static void	child_signal(int signo);

/**
 * @brief  Sets up signal handling for SIGINT (Ctrl-C) and SIGQUIT (Ctrl-\\).
 * 
 *  This function initializes the given signals with the respective signal.
 *  It also sets up the termios settings (terminal config) and how it should
 * 	behave.
 *  handlers for SIGINT and SIGQUIT.
 */
void	setup_signals(void)
{
	struct sigaction	sa_int;

	setup_termios_config();
	sa_int.sa_handler = handle_parent_signal;
	sa_int.sa_flags = SA_RESTART;
	sigemptyset(&sa_int.sa_mask);
	sigaction(SIGINT, &sa_int, NULL);
	sigaction(SIGQUIT, &sa_int, NULL);
}

static void handle_parent_signal(int signo)
{
	if (signo == SIGINT)
	{
		ft_fprintf(STDOUT_FILENO, "\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

static void	setup_termios_config(void)
{
	struct termios	termios_config;

	tcgetattr(0, &termios_config);
	termios_config.c_lflag &= ~ECHOCTL;
	tcsetattr(0, 0, &termios_config);
}

void	setup_child_signals(void)
{
	struct sigaction sa_default;

	sa_default.sa_handler = child_signal;
	sa_default.sa_flags = 0;
	sigemptyset(&sa_default.sa_mask);

	sigaction(SIGINT, &sa_default, NULL);
	sigaction(SIGQUIT, &sa_default, NULL);
	(void)child_signal;
}

static void	child_signal(int signo)
{
	if (signo == SIGINT)
	{
		ft_fprintf(STDOUT_FILENO, "\n");
		exit(1);
	}
	else if (signo == SIGQUIT)
		return ;
}
