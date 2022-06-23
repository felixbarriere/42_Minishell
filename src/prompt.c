/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarrier <fbarrier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 17:43:57 by fbarrier          #+#    #+#             */
/*   Updated: 2022/06/22 20:27:39 by fbarrier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/minishell_d.h"
#include "../include/minishell_f.h"
#include "../include/minishell_s.h"

// void	print_parser_result(t_sh *sh)
// {
// 	t_pipe *temp;
// 	int j;

// 	if (sh->error == 1)
// 		return;
// 	temp = sh->pipe_lst;
// 	j = 1;
// 	while (temp)
// 	{
// 		printf("***CMD_LINE %d ***\n", j);
// 		printf("tokens : \n");
// 		print_tokens(temp->token);
// 		printf("cmd=%s\n",temp->cmd);
// 		int i = 0;
// 		printf("args: [");
// 		while (temp->args[i])
// 		{
// 			printf("%s,", temp->args[i]);
// 			i++;
// 		}
// 		printf("]");
// 		printf("\nfdout=%d, fdin=%d\n", temp->output, temp->input);
// 		printf("heredoc_mode=%d, append_mode=%d\n"	, temp->heredoc_mode, temp->append_mode);
// 		printf("\n");
// 		temp = temp->next;
// 		j++;
// 	}
// }

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
		// free(env[i]);
		i++;
	}
	sh->env[i] = NULL;
	// free(env);
}

void	ft_prompt_start(t_sh *sh)
{
	sh->prompt = readline("➜ minishell ");
	if (!sh->prompt || !ft_strcmp(sh->prompt, "exit"))
	{
		ft_free(sh->path);
		ft_free(sh->env);
		clear_list(sh->token_lst);
		clear_list_pipe(sh->pipe_lst);
		exit(0);
	}
	add_history(sh->prompt);
}

void	ft_prompt_init(t_sh *sh, char **env_init)
{
	dup_env_array(sh, env_init);
	printf("test array env: %s\n", sh->env[3]);
	ft_init_values(sh, env_init);
	sh->exit = 0;
	ft_init_env(sh->env, sh);
	get_path(sh);
	while (1)
	{
		ft_prompt_start(sh);
		sh->lenght = ft_strlen(sh->prompt);
		if (!is_only_space(sh->prompt))
			lexer(sh);
		// printf("sh->error = %d\n", sh->error);
		if (sh->error)
		{
			clear_list(sh->token_lst);
			clear_list_pipe(sh->pipe_lst);
			ft_init_values(sh, env_init);
			sh->exit = 0;
			continue ;
		}
		// print_parser_result(sh);
		execution(sh, sh->env);
		printf("Le code de retour est %d\n",sh->exit);
		clear_list(sh->token_lst);
		clear_list_pipe(sh->pipe_lst);
		ft_init_values(sh, sh->env);
	}
}
