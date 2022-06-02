/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarrier <fbarrier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 18:18:11 by ccalas            #+#    #+#             */
/*   Updated: 2022/06/02 15:55:49 by fbarrier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/minishell_d.h"
#include "../include/minishell_f.h"
#include "../include/minishell_s.h"

void	ft_init_values(t_sh *sh, char **env)
{
	(void)env;
	sh->token_lst = NULL;
	sh->prompt = NULL;
	sh->p_index = 0;
	sh->e_index = 0;
	sh->lenght = 0;
	sh->state_quote = DEFAULT;

	sh->pipe_lst = ft_calloc(1, sizeof(t_pipe));
	if (!sh->pipe_lst)
		return ;
	sh->pipe_lst->cmd = ft_strdup("first");
	sh->pipe_lst->options = NULL;
	sh->pipe_lst->file = NULL;
	sh->pipe_lst->token = NULL;
	sh->pipe_lst->prev = NULL;
	sh->pipe_lst->next = NULL;

}
