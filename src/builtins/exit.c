/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarrier <fbarrier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 18:19:33 by fbarrier          #+#    #+#             */
/*   Updated: 2022/06/24 18:39:52 by fbarrier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/minishell_d.h"
#include "../../include/minishell_f.h"
#include "../../include/minishell_s.h"

void	exit_command(t_sh *sh)
{
	char *exit_nbr;

	printf("test\n");

	if(sh->pipe_lst->token->next)
	{
		printf("arg present\n");
		printf("==> %s\n", sh->pipe_lst->token->next->value);
		exit_nbr = sh->pipe_lst->token->next->value;
		if (exit_nbr)
		{
			sh->exit = ft_atoi(exit_nbr);
			printf("==> %d\n", sh->exit);
		}
		
	}
	// if(sh->pipe_lst->args[2])
	// {
	// 	printf("trop d'arg\n");
	// }
	
	ft_free(sh->path);
	ft_free(sh->env);
	clear_list(sh->token_lst);
	clear_list_pipe(sh->pipe_lst);
	exit(0);
}