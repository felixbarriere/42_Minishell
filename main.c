/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccalas <ccalas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 18:08:23 by marvin            #+#    #+#             */
/*   Updated: 2022/07/31 15:08:20 by ccalas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"
#include "include/minishell_d.h"
#include "include/minishell_f.h"
#include "include/minishell_s.h"

t_sh	g_sh;

void	last_cmd(t_sh *sh)
{
	t_pipe	*start;

	start = sh->pipe_lst;
	while (start->next)
		start = start->next;
	if (start && start->cmd_ok == 1)
		sh->exit = 127;
}

int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	if (isatty(0) == 0 || isatty(1) == 0)
		return (0);
	ft_memset(&g_sh, 0, sizeof(t_sh));
	if (ac != 1)
	{
		ft_putstr_fd("Error: wrong's args number\n", 2);
		exit(EXIT_FAILURE);
	}
	ft_prompt_init(&g_sh, env);
	clear_list_env(g_sh.env_lst);
	clear_list(g_sh.token_lst);
	if (g_sh.error == 1)
		return (1);
	return (0);
}
