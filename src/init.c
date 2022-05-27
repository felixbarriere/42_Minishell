/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarrier <fbarrier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 18:18:11 by ccalas            #+#    #+#             */
/*   Updated: 2022/05/27 17:59:46 by fbarrier         ###   ########.fr       */
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
}
