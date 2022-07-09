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

static void	ft_signal_handler(int signal)
{
	extern t_sh	g_sh;

	if (signal == SIGINT)
	{
		write(1, "\n", 1);
		g_sh.exit = 130;
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (signal == SIGSEGV)
	{
		write(1, "exit\n", 6);
		clear_list_env(g_sh.env_lst);
		clear_list(g_sh.token_lst);
		exit(0);
	}
}


void	ft_signals_orchestrator(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, ft_signal_handler);
	// signal(SIGINT, SIG_DFL);
}

