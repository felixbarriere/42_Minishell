/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccalas <ccalas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 18:08:23 by marvin            #+#    #+#             */
/*   Updated: 2022/05/03 17:17:34 by ccalas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"
#include "include/minishell_d.h"
#include "include/minishell_f.h"
#include "include/minishell_s.h"

int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;

	t_sh sh;
	if (ac != 1)
	{
		ft_putstr_fd("Erreur: nombre d'arguments\n", 2);
		exit(EXIT_FAILURE);
	}
	ft_signals_orchestrator();
	ft_prompt_init(&sh, env);

	// penser a free la liste chainee
	
	return (0);
}