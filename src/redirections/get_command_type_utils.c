/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_command_type_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarrier <fbarrier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 15:36:40 by fbarrier          #+#    #+#             */
/*   Updated: 2022/07/28 13:29:11 by fbarrier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/minishell_d.h"
#include "../../include/minishell_f.h"
#include "../../include/minishell_s.h"

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
		else if (lst->type == STR)
			find_type_args(lst, sh);
		lst = lst->next;
	}
	lst = temp;
}

void	get_commands_type(t_sh *sh)
{
	t_pipe	*temp;

	temp = sh->pipe_lst;
	if (!sh->pipe_lst)
		return ;
	while (sh->pipe_lst)
	{
		find_type(sh->pipe_lst->token, sh);
		sh->pipe_lst = sh->pipe_lst->next;
	}
	sh->pipe_lst = temp;
}

int	update_fdin_error(t_token *temp, t_pipe *pipe_lst)
{
	int		error;

	error = 0;
	if (temp->type == INPUT)
		error = open_fdin(temp->value, &pipe_lst);
	else
		error = heredoc(temp->value, &pipe_lst);
	return (error);
}
