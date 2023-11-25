/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwenz <cwenz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 12:32:52 by cwenz             #+#    #+#             */
/*   Updated: 2023/11/25 16:05:19 by cwenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_parent_signal(int signo);
static void	setup_termios_config(void);

/**
 * @brief  Sets up signal handling for SIGINT (Ctrl-C) and SIGQUIT (Ctrl-\\).
 * 
 *  This function initializes the given signals with the respective signal.
 *  It also sets up the termios settings (terminal config) and how it should
 * 	behave.
 */
void	setup_signals(void)
{
	struct sigaction	sa_int;

	setup_termios_config();
	sa_int.sa_handler = handle_parent_signal;
	sa_int.sa_flags = SA_RESTART;
	sigemptyset(&sa_int.sa_mask);
	sigaction(SIGINT, &sa_int, NULL);
	signal(SIGQUIT, SIG_IGN);
}

/// @brief Handles the SIGINT signal
/// @param signo The signal number
static void	handle_parent_signal(int signo)
{
	if (signo == SIGINT)
	{
		ft_fprintf(STDOUT_FILENO, "\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		set_exit_code(1);
	}
}

/// @brief Sets up the terminal config.
static void	setup_termios_config(void)
{
	struct termios	termios_config;

	tcgetattr(0, &termios_config);
	termios_config.c_lflag &= ~ECHOCTL;
	tcsetattr(0, 0, &termios_config);
}

void	setup_child_signals(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void	setup_heredoc_signals(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_IGN);
}
