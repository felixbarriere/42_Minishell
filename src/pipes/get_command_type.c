/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_command_type.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarrier <fbarrier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 19:28:11 by fbarrier          #+#    #+#             */
/*   Updated: 2022/06/10 14:06:33 by ccalas           ###   ########.fr       */
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

int	update_args(t_pipe **pipe_lst)
{
	t_token	*token;
	int		i;

	token = (*pipe_lst)->token;
	(*pipe_lst)->args = ft_calloc(args_number(token) + 1, sizeof(char *));
	if (!(*pipe_lst)->args)
		return (1);
	i = 0;
	while (token)
	{
		if (token->type == CMD || token->type == ARG)
		{
			(*pipe_lst)->args[i] = ft_strdup(token->value);
			if (!(*pipe_lst)->args[i])
				return (1);
			i++;
		}
		token = token->next;
	}
	(*pipe_lst)->args[i] = NULL;
	return (0);
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

int	is_cmd(t_token *lst, t_sh *sh)
{
	t_token *temp;

	temp = lst;
	while (lst)
	{
		if (!sh->pipe_lst->cmd)
			return (1);
		lst = lst->next;
	}
	lst = temp;
	return (0);
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
	// update_args(&sh->pipe_lst);
}

void	get_commands_type(t_sh *sh)
{
	t_pipe	*temp;
	// int		i;

	temp = sh->pipe_lst;
	if (!sh->pipe_lst)
		return ;
	while (sh->pipe_lst)
	{
		find_type(sh->pipe_lst->token, sh);
		sh->pipe_lst = sh->pipe_lst->next;
	}
	// i = 0;
	// printf("COMMAND = %s\n", temp->cmd);
	// while (temp->args[i] != NULL)
	// {
	// 	printf("ARG = %s\n", temp->args[i]);
	// 	i++;
	// }
	sh->pipe_lst = temp;
}

void	update_command(t_sh *sh)
{
	// get_commands_type(sh);
	t_pipe *temp;

	temp = sh->pipe_lst;
	printf("OUPUT WAY BEFORE = %d\n", sh->pipe_lst->output);
	while (sh->pipe_lst)
	{
		if (is_cmd(sh->token_lst, sh))
			sh->error = 1;
		if (update_args(&sh->pipe_lst))
			sh->error = 1;
		if (update_fdout(&sh->pipe_lst))
			sh->error = 1;
		if (update_fdin(&sh->pipe_lst))
		{
			sh->error = 1;
		}
		sh->pipe_lst = sh->pipe_lst->next;
	}
	printf("COMMAND UPDATE = %s\n", temp->cmd);
	printf("COMMAND = %s\n", temp->cmd);
	int i = 0;
	while (temp->args[i] != NULL)
	{
		printf("ARG = %s\n", temp->args[i]);
		i++;
	}
	sh->pipe_lst = temp;
}
