/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jji <jji@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 15:19:58 by jji               #+#    #+#             */
/*   Updated: 2021/12/02 15:19:59 by jji              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	sig_restart(int sig)
{
	if (sig == SIGINT)
	{
		write(STDOUT_FILENO, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_exit_code = 1;
		(void)sig;
	}
}

void	blocking_ctrl_c(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n", 1);
}

void	blocking_back_slash(int sig)
{
	(void)sig;
	ft_putstr_fd("Quit: 3\n", STDOUT_FILENO);
}

void	emit_signal(int sig)
{
	if (sig == OMIT)
	{
		signal(SIGINT, sig_restart);
		signal(SIGQUIT, SIG_IGN);
	}
	if (sig == N_OMIT)
	{
		signal(SIGINT, blocking_ctrl_c);
		signal(SIGQUIT, blocking_back_slash);
	}
}

void	switch_echoctl(int sig)
{
	struct termios	new_term;

	tcgetattr(STDIN_FILENO, &new_term);
	if (sig == TURN_OFF)
		new_term.c_lflag &= ~ECHOCTL;
	else
		new_term.c_lflag |= ECHOCTL;
	new_term.c_cc[VMIN] = 1;
	new_term.c_cc[VTIME] = 0;
	tcsetattr(STDIN_FILENO, TCSANOW, &new_term);
}
