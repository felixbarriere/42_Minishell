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

static void ft_signal_handler(int signal)
{
	if (signal == SIGINT)
	{
		/* créer un système de définition d'erreurs à renvoyer */
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (signal == SIGSEGV)
	{
		/* créer un système de définition d'erreurs à renvoyer */
		write(1, "exit\n", 6);
		// a free
		exit(0);
	}
}

void	ft_signals_orchestrator(void)
{
	signal(SIGQUIT, SIG_IGN);			/**** on ignore "ctrl_\" ****/
	signal(SIGINT, ft_signal_handler);  /**** on gère "ctrl_C" ****/
	signal(SIGSEGV, ft_signal_handler);	/**** on gère "ctrl_D" ****/
}

