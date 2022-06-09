/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_command_type.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarrier <fbarrier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 19:28:11 by fbarrier          #+#    #+#             */
/*   Updated: 2022/06/09 17:20:39 by fbarrier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/minishell_d.h"
#include "../../include/minishell_f.h"
#include "../../include/minishell_s.h"

int	args_number(t_token *li)
{
	int	i;

	i = 0;
	while (li != NULL)
	{
		if (li->type == ARG || li->type == CMD)
			i++;
		li = li->next;
	}
	return (i);
}

void	update_args(t_pipe **pipe_lst)
{
	t_token	*token;
	int		i;

	token = (*pipe_lst)->token;
	(*pipe_lst)->args = ft_calloc(args_number(token) + 1, sizeof(char *));
	if (!(*pipe_lst)->args)
		return ;
	i = 0;
	while (token)
	{
		if (token->type == CMD || token->type == ARG)
		{
			(*pipe_lst)->args[i] = ft_strdup(token->value);
			if (!(*pipe_lst)->args[i])
				return ;
			i++;
		}
		token = token->next;
	}
	(*pipe_lst)->args[i] = NULL;
	return ;
}

void	find_type_args(t_token *lst, t_sh *sh)
{
	(void)sh;
	if (!lst)
		return ;
	while (lst)
	{
		if (lst->type == STR)
		{
			lst->type = CMD;
			sh->pipe_lst->cmd = ft_strdup(lst->value);
			break ;
		}
		lst = lst->next;
	}
	while (lst)
	{
		if (lst->type == STR)
			lst->type = ARG;
		lst = lst->next;
	}
}

void	find_type(t_token *lst, t_sh *sh)
{
	t_token	*temp;

	temp = lst;
	if (!lst)
		return ;
	while (lst)
	{
		if (lst->type == R_LEFT)
			lst->next->type = INPUT;
		else if (lst->type == R_RIGHT)
			lst->next->type = OUTPUT;
		else if (lst->type == DR_RIGHT)
			lst->next->type = APPEND;
		else if (lst->type == LIMITER)
			sh->pipe_lst->limiter = ft_strdup(lst->value);
		else if (lst->type == STR)
			find_type_args(lst, sh);
		lst = lst->next;
	}
	lst = temp;
	printf("------APRES-----\n");
	print_tokens(lst);
	update_args(&sh->pipe_lst);
}

void	get_commands_type(t_sh *sh)
{
	t_pipe	*temp;
	int		i;

	temp = sh->pipe_lst;
	if (!sh->pipe_lst)
		return ;
	while (sh->pipe_lst)
	{
		find_type(sh->pipe_lst->token, sh);
		sh->pipe_lst = sh->pipe_lst->next;
	}
	i = 0;
	while (temp->args[i] != NULL)
	{
		printf("ARG = %s\n", temp->args[i]);
		i++;
	}
	sh->pipe_lst = temp;
}
