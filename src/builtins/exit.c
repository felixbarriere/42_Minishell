/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 18:19:33 by fbarrier          #+#    #+#             */
/*   Updated: 2022/07/18 17:42:02 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/minishell_d.h"
#include "../../include/minishell_f.h"
#include "../../include/minishell_s.h"

void	exit_command_2(t_sh *sh, t_pipe *pipe_lst)
{
	if (sh->path != NULL)
		ft_free(sh->path);
	ft_free(sh->env);
	clear_list(sh->token_lst);
	clear_list_pipe(pipe_lst);
	if (sh->exit)
		exit(sh->exit);
	else
		exit(2);
}

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

int	too_many_chars(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	if (i >= 20)
		return (1);
	return (0);
}

void	exit_error(t_token *temp, t_sh *sh, char *exit_nbr)
{
	if (ft_atoi(temp->next->value) < 0 && !too_many_chars(exit_nbr))
	{
		sh->exit = 2;
		return ;
	}
	if (!is_in_range(temp->next->value) || ft_atoi(temp->next->value) >= 255
		|| too_many_chars(exit_nbr))
	{
		ft_putstr_fd("exit: ", 2);
		ft_putstr_fd(temp->next->value, 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		sh->exit = 2;
	}
}

void	exit_command(t_sh *sh, t_pipe *pipe_lst)
{
	t_token	*temp;

	temp = pipe_lst->token;
	while (temp && temp->type != CMD)
		temp = temp->next;
	if (temp)
	{
		ft_putstr_fd("exit\n", 1);
		if (temp->next && temp->next->type == ARG)
		{
			if (is_in_range(temp->next->value) && ft_atoi(temp->next->value)
				<= 255 && !temp->next->next
					&& !too_many_chars(temp->next->value))
				sh->exit = ft_atoi(temp->next->value);
			else if (temp->next->next && is_in_range(temp->next->value))
			{
				ft_putstr_fd("exit: too many arguments\n", 2);
				sh->exit = 1;
				return ;
			}
			else
				exit_error(temp, sh, temp->next->value);
		}
		exit_command_2(sh, pipe_lst);
	}
}

// CASES
// exit hh jj:doit qd meme exit
// exit hhh 45 34: doit qd meme sortir
// exit 22222222222222222222222 (20 chiffres): nu;eric argument required

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
