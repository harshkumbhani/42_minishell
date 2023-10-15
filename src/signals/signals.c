/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwenz <cwenz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 12:32:52 by cwenz             #+#    #+#             */
/*   Updated: 2023/10/15 13:31:35 by cwenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void handle_sigint(int signo, siginfo_t *siginfo, void *context);
static void handle_sigquit(int signo, siginfo_t *siginfo, void *context);

/**
 * @brief  Sets up signal handling for SIGINT (Ctrl-C) and SIGQUIT (Ctrl-\\).
 * 
 *  This function initializes the given signals with the respective signal
 *  handlers for SIGINT and SIGQUIT.
 */
void    setup_signals()
{
	struct sigaction sa_int;
	struct sigaction sa_quit;
	
	sa_int.sa_sigaction = handle_sigint;
	sa_int.sa_flags = SA_SIGINFO; // Probably these flags are not needed, will change most likely
	sigemptyset(&sa_int.sa_mask); // Don't block any signals during this signals handling, probably have to change
	sigaction(SIGINT, &sa_int, NULL);

	sa_quit.sa_sigaction = handle_sigquit;
	sa_quit.sa_flags = SA_SIGINFO; // Probably these flags are not needed, will change most likely
	sigemptyset(&sa_quit.sa_mask); // Don't block any signals during this signals handling, probably have to change
	sigaction(SIGQUIT, &sa_quit, NULL);
}


/**
 * @brief 
 * @param signo 
 * @param siginfo 
 * @param context 
 */
static void handle_sigint(int signo, siginfo_t *siginfo, void *context)
{
	printf("\nSIGINT executed! Ctrl-C pressed!\n");
	(void)signo;
	(void)siginfo;
	(void)context;
}

/**
 * @brief 
 * @param signo 
 * @param siginfo 
 * @param context 
 */
static void handle_sigquit(int signo, siginfo_t *siginfo, void *context)
{
	printf("\nSIGQUIT executed! Ctrl-\\ pressed!\n");
	(void)signo;
	(void)siginfo;
	(void)context;
}
