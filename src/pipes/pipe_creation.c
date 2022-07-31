/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_creation.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccalas <ccalas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 16:17:44 by fbarrier          #+#    #+#             */
/*   Updated: 2022/07/31 14:26:09 by ccalas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/minishell_d.h"
#include "../../include/minishell_f.h"
#include "../../include/minishell_s.h"

void	print_pipe_tokens(t_pipe *li)
{
	while (li != NULL)
	{
		printf("\n");
		if (li->token != NULL)
			printf("pipe_token: [%s] ", li->token->value);
		li = li->next;
	}
	printf("\n");
}

t_pipe	*create_pipe_token(void)
{
	t_pipe	*elem;

	elem = ft_calloc(1, sizeof(t_pipe));
	if (!elem)
		return (NULL);
	elem->cmd = NULL;
	elem->cmd_ok = 0;
	elem->pipe_ok = 0;
	elem->token = NULL;
	elem->prev = NULL;
	elem->next = NULL;
	elem->input = 0;
	elem->output = 1;
	elem->append_mode = 0;
	elem->heredoc_mode = 0;
	return (elem);
}

t_pipe	*add_back_pipe_token(t_pipe *pipe_lst)
{
	t_pipe	*new;
	t_pipe	*tmp;

	tmp = NULL;
	new = create_pipe_token();
	if (!new)
		return (NULL);
	if (pipe_lst->token)
	{
		tmp = pipe_lst;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
		new->prev = tmp;
	}
	return (tmp);
}

void	pipe_creation(t_sh *sh)
{	
	t_pipe	*pipe_start;
	t_token	*token_start;

	token_start = sh->token_lst;
	if (sh->pipe_lst->token)
		sh->pipe_lst = add_back_pipe_token(sh->pipe_lst);
	pipe_start = sh->pipe_lst;
	while (sh->token_lst != NULL)
	{
		if (sh->token_lst->type != PIPE)
		{
			sh->pipe_lst->token = add_back_token(sh->pipe_lst->token,
					sh->token_lst->type, sh->token_lst->value);
			sh->token_lst = sh->token_lst->next;
		}
		else
		{
			sh->pipe_lst = add_back_pipe_token(sh->pipe_lst);
			sh->pipe_lst = sh->pipe_lst->next;
			sh->token_lst = sh->token_lst->next;
		}
	}
	sh->pipe_lst = pipe_start;
	sh->token_lst = token_start;
}
