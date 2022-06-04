/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccalas <ccalas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 17:43:57 by fbarrier          #+#    #+#             */
/*   Updated: 2022/06/04 15:34:25 by ccalas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/minishell_d.h"
#include "../include/minishell_f.h"
#include "../include/minishell_s.h"

void	ft_prompt_start(t_sh *sh)
{
	sh->prompt = readline("➜ minishell ");
	if (!sh->prompt || !ft_strcmp(sh->prompt, "exit"))
	{
		clear_list(sh->token_lst);
		clear_list_pipe(sh->pipe_lst);
		ft_free(sh->path);
		exit(0);
	}
	add_history(sh->prompt);
}

void	ft_prompt_init(t_sh *sh, char **env_init)
{
	ft_init_values(sh, env_init);
	ft_init_env(env_init, sh);
	get_path(sh);

	while (1)
	{
		ft_prompt_start(sh);
		sh->lenght = ft_strlen(sh->prompt);
		if (!is_only_space(sh->prompt))
			lexer(sh);
		clear_list(sh->token_lst);
		clear_list_pipe(sh->pipe_lst);
		ft_init_values(sh, env_init);
	}
}
