/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_command_type.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccalas <ccalas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 19:28:11 by fbarrier          #+#    #+#             */
/*   Updated: 2022/07/27 16:24:18 by ccalas           ###   ########.fr       */
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

int	is_cmd(t_token *lst, t_sh *sh)
{
	t_token	*temp;

	temp = lst;
	while (lst)
	{
		if (lst->type == CMD)
		{
			if (!sh->pipe_lst->cmd)
				return (1);
		}
		lst = lst->next;
	}
	lst = temp;
	return (0);
}

void	update_command(t_sh *sh)
{
	t_pipe	*temp;
	int		i;

	temp = sh->pipe_lst;
	while (sh->pipe_lst)
	{
		if (is_cmd(sh->token_lst, sh) == 1)
			sh->error = 1;
		if (update_args(&sh->pipe_lst) == 1)
			sh->error = 1;
		i = update_fdin(&sh->pipe_lst);
		if (i == 1)
			sh->error = 1;
		else if (i == 2)
			return ;
		sh->pipe_lst = sh->pipe_lst->next;
	}
	sh->pipe_lst = temp;
}
