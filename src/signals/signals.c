/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwenz <cwenz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 12:32:52 by cwenz             #+#    #+#             */
/*   Updated: 2023/11/12 15:05:12 by cwenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

static void handle_sigint(int signo);
static void handle_sigquit(int signo);
static void	setup_termios_config();

/**
 * @brief  Sets up signal handling for SIGINT (Ctrl-C) and SIGQUIT (Ctrl-\\).
 * 
 *  This function initializes the given signals with the respective signal.
 *  It also sets up the termios settings (terminal config) and how it should
 * 	behave.
 *  handlers for SIGINT and SIGQUIT.
 */
void	setup_signals()
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;
	

	setup_termios_config();
	sa_int.sa_handler = handle_sigint;
	sa_int.sa_flags = 0;
	sigemptyset(&sa_int.sa_mask);
	sigaction(SIGINT, &sa_int, NULL);

	sa_quit.sa_handler = handle_sigquit;
	sa_quit.sa_flags = 0;
	sigemptyset(&sa_quit.sa_mask);
	sigaction(SIGQUIT, &sa_quit, NULL);
}

static void handle_sigint(int signo)
{
	ft_fprintf(STDOUT_FILENO, "\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	(void)signo;
}

static void handle_sigquit(int signo)
{
	exit(0);
	(void)signo;
}

static void	setup_termios_config()
{
	struct termios	termios_config;

	tcgetattr(0, &termios_config);
	termios_config.c_lflag &= ~ECHOCTL;
	tcsetattr(0, 0, &termios_config);
}
