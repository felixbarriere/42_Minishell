/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarrier <fbarrier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 18:08:23 by marvin            #+#    #+#             */
/*   Updated: 2022/05/24 18:27:58 by fbarrier         ###   ########.fr       */
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
	ft_memset(&sh, 0, sizeof(t_sh));
	if (ac != 1)
	{
		ft_putstr_fd("Error: wrong's args number\n", 2);
		exit(EXIT_FAILURE);
	}
	ft_signals_orchestrator();
	ft_prompt_init(&sh, env);

	// ft_free_2(sh.env_lst->key);
	// ft_free_2(sh.env_lst->value);
	// ft_free_2(sh.env_lst->full);
	// ft_free_3(sh.env_lst); // attention car clear_list free deja.
	// penser a free la liste chainee
	printf("test_leaks\n");
	clear_list_env(sh.env_lst);
	clear_list(sh.token_lst);
	return (0);
}