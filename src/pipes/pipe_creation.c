/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_creation.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 16:17:44 by fbarrier          #+#    #+#             */
/*   Updated: 2022/07/06 18:05:04 by marvin           ###   ########.fr       */
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
			printf("[%s] ", li->token->value);
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
	elem->file = NULL;
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
	if (pipe_lst->cmd)
	{
		printf("pipe_lst != NULL\n");
	}
	new = create_pipe_token();
	if (!new)
		return (NULL);
	if (!pipe_lst->cmd)
	{
		printf("pipe == NULL\n");
		return (new);
	}
	else
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
	if (sh->pipe_lst)
		printf("pipe test first\n");
	if (sh->pipe_lst->next)
		printf("pipe next test first\n");
	sh->pipe_lst = add_back_pipe_token(sh->pipe_lst);
	if (sh->pipe_lst)
		printf("pipe test\n");
	if (sh->pipe_lst->next)
		printf("pipe next test\n");
	pipe_start = sh->pipe_lst;
	while (sh->token_lst != NULL)
	{
		if (sh->token_lst->type != PIPE)
		{
			printf("\ntest pipe\n");
			sh->pipe_lst->token = add_back_token(sh->pipe_lst->token,
					sh->token_lst->type, sh->token_lst->value);
			if (sh->token_lst->next != NULL)
				sh->token_lst = sh->token_lst->next;
			else
				break;
		}
		else
		{
			sh->pipe_lst = add_back_pipe_token(sh->pipe_lst);
			sh->token_lst = sh->token_lst->next;
		}
	}
	sh->pipe_lst = pipe_start;
	sh->token_lst = token_start;
}
