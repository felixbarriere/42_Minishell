/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccalas <ccalas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 18:18:11 by ccalas            #+#    #+#             */
/*   Updated: 2022/05/05 17:59:26 by ccalas           ###   ########.fr       */
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
	sh->env_lst = NULL;
	sh->prompt = NULL;
	sh->p_index = 0;
	sh->e_index = 0;
	sh->lenght = 0;
	sh->state_quote = DEFAULT;
	// sh->env_lst = ft_init_env(env, sh);
	// test env: 
	// int i = 0;
	// while(sh->env[i])
	// {
	// 	printf("%s\n", sh->env[i++]);
	// }
}


// void	ft_init_env_values(t_env *env)
// {
// 	// env->value = NULL;
// 	// env->key = NULL;
// 	// env->full = NULL;
// 	env->index = 0;
// 	// (void)env;
// 	printf("hello");
// }