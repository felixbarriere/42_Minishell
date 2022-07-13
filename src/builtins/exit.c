/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccalas <ccalas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 18:19:33 by fbarrier          #+#    #+#             */
/*   Updated: 2022/07/09 12:16:41 by ccalas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/minishell_d.h"
#include "../../include/minishell_f.h"
#include "../../include/minishell_s.h"

int	is_in_range(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_isdigit(str[i]) == 1)
			i++;
		else
			return (0);
	}
	return (1);
}



void	exit_command(t_sh *sh, t_pipe *pipe_lst)
{
	char	*exit_nbr;
	t_token *temp;

	temp = pipe_lst->token;
	while (temp && temp->type != CMD)
		temp = temp->next;
	if (temp)
	{
		if (temp->next && temp->next->type == ARG)
		{
			exit_nbr = temp->next->value;
			if (is_in_range(exit_nbr) && ft_atoi(exit_nbr) <= 255
					&& !temp->next->next)
				sh->exit = ft_atoi(exit_nbr);
			else
			{
				ft_putstr_fd("exit: bad argument\n", 2);
				return ;
			}
		}
		if (sh->path != NULL)
		{
			printf("sh->path existe\n");
			ft_free(sh->path);
		}
		ft_free(sh->env);
		clear_list(sh->token_lst);
		clear_list_pipe(pipe_lst);
		if (sh->exit)
			exit(sh->exit);
		else
			exit(2);
	}
}



// void	exit_command(t_sh *sh)
// {
// 	char	*exit_nbr;

// 	if (sh->pipe_lst->token->next)
// 	{
// 		exit_nbr = sh->pipe_lst->token->next->value;
// 		if (exit_nbr && is_in_range(exit_nbr) && ft_atoi(exit_nbr) <= 255
// 			&& !sh->pipe_lst->token->next->next)
// 			sh->exit = ft_atoi(exit_nbr);
// 		else
// 		{
// 			ft_putstr_fd("exit: bad argument\n", 2);
// 			return ;
// 		}
// 	}
// 	if (sh->path != NULL)
// 	{
// 		printf("sh->path existe\n");
// 		ft_free(sh->path);
// 	}
// 	ft_free(sh->env);
// 	clear_list(sh->token_lst);
// 	clear_list_pipe(sh->pipe_lst);
// 	if (sh->exit)
// 	{
// 			printf("ICI\n");
// 			exit(sh->exit);
// 	}
// 		else
// 		{
// 			printf("ICI 2\n");
// 			exit(2);
// 		}
// }
