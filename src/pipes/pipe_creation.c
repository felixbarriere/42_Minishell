/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_creation.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarrier <fbarrier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 16:17:44 by fbarrier          #+#    #+#             */
/*   Updated: 2022/06/01 17:24:35 by fbarrier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/minishell_d.h"
#include "../../include/minishell_f.h"
#include "../../include/minishell_s.h"

t_pipe	*create_pipe_token(void)
{
	t_pipe	*elem;

	elem = ft_calloc(1, sizeof(t_pipe));
	if (!elem)
		return (NULL);
	elem->cmd = NULL;
	elem->options = NULL;
	elem->file = NULL;
	elem->token = NULL;
	elem->prev = NULL;
	elem->next = NULL;
	return (elem);
}

t_pipe	*add_back_pipe_token(t_pipe *pipe_lst)
{
	t_pipe	*new;
	t_pipe	*tmp;

	tmp = NULL;
	// (void)value;
	new = create_pipe_token();
	if (!new)
		return (NULL);
	if (!pipe_lst)
		return (new);
	else
	{
		tmp = pipe_lst;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
		new->prev = tmp;
	}
	// free(new);
	// free(tmp);
	return (tmp);
}

void	pipe_creation(t_sh *sh)
{	
	t_pipe 	*pipe_start;
	t_token	*token_start;

	token_start = sh->token_lst;
	sh->pipe_lst = add_back_pipe_token(sh->pipe_lst);
	
	pipe_start = sh->pipe_lst;

	while (sh->token_lst != NULL)
	{
		if (sh->token_lst != NULL && sh->token_lst->type != PIPE)
		{
			sh->pipe_lst->token = add_back_token(sh->pipe_lst->token, sh->token_lst->type, sh->token_lst->value);
			sh->token_lst = sh->token_lst->next;
			// (*pipe_lst)->token = (*pipe_lst)->token->next;  //pas obligatoire si add back
		}
		else 
		{			
			sh->pipe_lst = add_back_pipe_token(sh->pipe_lst);
			if (sh->token_lst != NULL)
				sh->token_lst = sh->token_lst->next;
		}
	}
	sh->pipe_lst = pipe_start;
	sh->token_lst = token_start;
	// printf("pipe final: %s\n", pipe_start->token->value);
	// printf("token final: %s\n", token_start->value);
}



// void	pipe_creation(t_token **token_lst,t_pipe **pipe_lst, t_pipe **pipe_start, t_token **token_start)
// {	
// 	int	i = 0;
// 	*pipe_lst = add_back_pipe_token(*pipe_lst);
	
// 	*pipe_start = *pipe_lst;

// 	while (*token_lst != NULL)
// 	{
		

// 		if ((*token_lst) != NULL && (*token_lst)->type != PIPE)
// 		{
// 			printf("TOKEN IN PIPE %d\n", i);
// 			// (*pipe_lst)->token = *token_lst;

// 			(*pipe_lst)->token = add_back_token((*pipe_lst)->token, (*token_lst)->type, (*token_lst)->value);

// 			printf("token inter: %s\n", (*token_lst)->value);			
// 			*token_lst = (*token_lst)->next;
// 			// (*pipe_lst)->token = (*pipe_lst)->token->next;  //pas obligatoire si add back
// 		}

// 		else 
// 		{
// 			printf("PIPE_LIST %d\n", i);
			
// 			*pipe_lst = add_back_pipe_token(*pipe_lst);
// 			if (*token_lst != NULL)
// 			*token_lst = (*token_lst)->next;
// 			i++;
// 		}
// 	}
// 	*pipe_lst = *pipe_start;
// 	*token_lst = *token_start;
// 	// printf("pipe final: %s\n", (*pipe_lst)->cmd);
// 	printf("pipe final: %s\n", (*pipe_start)->token->value);
// 	printf("token final: %s\n", (*token_start)->value);
// }
