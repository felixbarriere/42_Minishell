/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccalas <ccalas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 17:43:57 by fbarrier          #+#    #+#             */
/*   Updated: 2022/08/01 16:51:23 by ccalas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/minishell_d.h"
#include "../include/minishell_f.h"
#include "../include/minishell_s.h"

void	dup_env_array(t_sh *sh, char **env)
{
	int	i;

	i = 0;
	while (env[i] != NULL)
		i++;
	sh->env = malloc (sizeof(char *) * (i + 1));
	if (!sh->env)
		return ;
	i = 0;
	while (env[i] != NULL)
	{
		sh->env[i] = ft_strdup(env[i]);
		i++;
	}
	sh->env[i] = NULL;
}

void	ft_close_final(void)
{
	int	i;

	i = 2;
	close(0);
	close(1);
	while (i < 1024)
	{
		if (!read(i, 0, 0))
			close(i);
		i++;
	}
}

void	ft_prompt_start(t_sh *sh)
{
	sh->prompt = readline("➜ minishell ");
	if (!sh->prompt)
	{
		ft_putstr_fd("\nexit\n", 1);
		free_free_all(sh);
		exit(0);
	}
	if (ft_strcmp(sh->prompt, ""))
		add_history(sh->prompt);
}

void	ft_prompt_init2(t_sh *sh, char **env_init)
{
	dup_env_array(sh, env_init);
	ft_init_values(sh, env_init);
	sh->exit = 0;
	ft_init_env(sh->env, sh);
	get_path(sh);
}

void	ft_prompt_init(t_sh *sh, char **env_init)
{
	ft_prompt_init2(sh, env_init);
	while (1)
	{
		ft_signals_orchestrator(0);
		ft_prompt_start(sh);
		sh->lenght = ft_strlen(sh->prompt);
		if (!is_only_space(sh->prompt))
			lexer(sh);
		if (sh->error && sh->error != 3)
		{
			clear_list(sh->token_lst);
			clear_list_pipe(sh->pipe_lst);
			ft_init_values(sh, env_init);
			continue ;
		}
		if (!ft_strcmp(sh->pipe_lst->cmd, "echo"))
			sh->exit = 0;
		if (!is_only_space(sh->prompt))
			execution(sh, sh->env, 0, NULL);
		if (nb_pipe(sh->pipe_lst))
			last_cmd(sh);
		clear_list(sh->token_lst);
		clear_list_pipe(sh->pipe_lst);
		ft_init_values(sh, sh->env);
	}
}
