/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 18:08:23 by marvin            #+#    #+#             */
/*   Updated: 2022/04/20 18:08:24 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"
#include "include/minishell_d.h"
#include "include/minishell_f.h"
#include "include/minishell_s.h"

void	ft_init_values(t_sh *sh)
{
	sh->token_lst = NULL;
	sh->prompt = NULL;
	sh->p_index = 0;
	sh->lenght = 0;
	sh->state_quote = DEFAULT;
	sh->env = ft_init_env();
}

int	main(int ac, char **av)
{
	(void)ac;
	(void)av;

	t_sh sh;
	if (ac != 1)
	{
		ft_putstr_fd("Erreur: nombre d'arguments \n", 2);
		exit(FAILURE);
	}
	ft_signals_orchestrator();
	ft_prompt_init(&sh);
	
	
	return (0);
}