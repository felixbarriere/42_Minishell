/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarrier <fbarrier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 15:53:50 by fbarrier          #+#    #+#             */
/*   Updated: 2022/04/19 15:53:50 by fbarrier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/minishell_d.h"
#include "../include/minishell_f.h"
#include "../include/minishell_s.h"

extern t_sh	g_sh;

static void	ft_signal_handler(int signal)
{
	if (signal == SIGINT)
	{
		ft_putstr_fd("\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_sh.exit = 130;
	}
}

void	heredoc_handler(int signal)
{
	if (signal == SIGINT)
	{
		ft_putstr_fd("\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		g_sh.error = 1;
		g_sh.exit = 130;
		free(g_sh.limiter);
		free_free_all(&g_sh);
		exit (130);
	}
}

void	ft_sigquit_handler(int signal)
{
	if (signal == SIGQUIT)
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		g_sh.error = 1;
		g_sh.exit = 131;
		free(g_sh.limiter);
		free_free_all(&g_sh);
		exit (131);
	}
}

void	ft_signals_orchestrator(int sigquit_active)
{
	signal(SIGINT, ft_signal_handler);
	if (sigquit_active)
		signal(SIGQUIT, ft_sigquit_handler);
	else
		signal(SIGQUIT, SIG_IGN);
}
