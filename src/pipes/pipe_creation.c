/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_creation.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarrier <fbarrier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 16:17:44 by fbarrier          #+#    #+#             */
/*   Updated: 2022/06/01 13:05:30 by fbarrier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/minishell_d.h"
#include "../../include/minishell_f.h"
#include "../../include/minishell_s.h"

t_pipe	*create_pipe_token(t_token *value)
{
	t_pipe	*elem;

	elem = ft_calloc(1, sizeof(t_pipe));
	if (!elem)
		return (NULL);
	elem->cmd = NULL;
	elem->options = NULL;
	elem->file = NULL;
	elem->token = value;
	elem->prev = NULL;
	elem->next = NULL;
	return (elem);
}

t_pipe	*add_back_pipe_token(t_pipe *pipe_lst, t_token *value)
{
	t_pipe	*new;
	t_pipe	*tmp;

	tmp = NULL;
	// (void)value;
	new = create_pipe_token(value);
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

void	pipe_creation(t_token **token_lst,t_pipe **pipe_lst, t_pipe **pipe_start, t_token **token_start)
{	
	// t_pipe	pipe_lst;
	int	i = 0;
	// t_token	*token = sh->pipe_lst->token;
	// t_pipe	*pipe = sh->pipe_lst;
	// t_sh	*sh = sh;
	
	// *pipe_lst = NULL;
	// printf("pipe: %s\n", (*pipe_lst)->cmd);
	// printf("token: %s\n", (*token_lst)->value);
	
	// printf("token final: %s\n", (*token_start)->value);



	while (*token_lst != NULL)
	{
		if ((*token_lst)->type != PIPE)
		{
			printf("PIPE_LIST %d\n", i);
			
			*pipe_lst = add_back_pipe_token(*pipe_lst, *token_lst);
			// printf("pipe final: %s\n", (*pipe_lst)->token->value);
			*token_lst = (*token_lst)->next;
		}

		while ((*token_lst) != NULL && (*token_lst)->type != PIPE)
		{
			printf("TOKEN IN PIPE %d\n", i);
			(*pipe_lst)->token = *token_lst;

			// sh->pipe_lst->token = add_back_token_in_pipe(sh->pipe_lst->token, sh->token_lst);

			
			*token_lst = (*token_lst)->next;
			(*pipe_lst)->token = (*pipe_lst)->token->next;
		}
		
		i++;
		if (*token_lst != NULL)
			*token_lst = (*token_lst)->next;
		if (*pipe_lst)
			*pipe_lst = (*pipe_lst)->next; //normalement pas obligatoire
	}
	*pipe_lst = *pipe_start;
	*token_lst = *token_start;
	// printf("====>%s\n", (*pipe_lst)->token->value);
	// printf("pipe final: %s\n", (*pipe_lst)->cmd);
	// // printf("pipe_final: %s\n", sh->pipe_lst->prev->token->value);
	// // sh->token_lst = sh->token_lst->prev;
	// printf("token final: %s\n", (*token_start)->value);
	
	


	// while (sh->token_lst->prev)
	// {
	// 	// printf("pipe final: %s\n", sh->token_lst->value);
	// }
	// sh->token_lst = sh->token_lst->prev;
	// printf("pipe final: %s\n", sh->token_lst->prev->value);
}
















// t_token	*create_token_in_pipe(t_token *value)
// {
// 	t_token	*elem;

// 	elem = ft_calloc(1, sizeof(t_token));
// 	if (!elem)
// 		return (NULL);
// 	elem = value;
// 	return (elem);
// }

// t_token	*add_back_token_in_pipe(t_token *list, t_token *value)
// {
// 	t_token	*new;
// 	t_token	*tmp;

// 	tmp = NULL;
// 	new = create_token_in_pipe(value);
// 	printf("test value token 2: %s\n", value->value);
// 	// new = value;
// 	if (!new)
// 		return (NULL);
// 	if (!list)
// 		return (new);
// 	else
// 	{
// 		tmp = list;
// 		printf("test value token 3: %s\n", tmp->value);
// 		printf("test value token next: %s\n", tmp->next->value);
// 		// printf("test value token next next: %s\n", tmp->next->next->value);
// 		// printf("test value token next next next: %s\n", tmp->next->next->next->value);
// 		// printf("test value token next next next next: %s\n", tmp->next->next->next->next->value);
// 		while (tmp->next != NULL)
// 		{
// 			// printf("test value token 2: %s\n", tmp->value);
// 			tmp = tmp->next;
// 		}
// 		tmp->next = new;
// 	}
// 	// free(new);
// 	// free(tmp);
// 	return (list);
// }


// void	pipe_creation(t_sh *sh)
// {	
// 	// t_pipe	*pipe_lst;
// 	int	i = 0;
// 	t_token	*temp_token = sh->pipe_lst->token;
// 	t_token	*temp_token_init = sh->token_lst;
// 	t_pipe	*temp_pipe;

// 	// t_sh	*temp_sh = sh;
	
// 	// sh->pipe_lst = NULL;

// 	// sh->pipe_lst = add_back_pipe_token(sh->pipe_lst, temp_token_init);
// 	temp_pipe = sh->pipe_lst;

// 	while (temp_token_init != NULL)
// 	{
// 		if (temp_token_init->type != PIPE)
// 		{
// 			printf("PIPE_LIST %d\n", i);
// 			add_back_pipe_token(temp_pipe, temp_token_init);
// 			printf("pipe: %s\n", temp_pipe->token->value);
// 			// temp_token_init = temp_token_init->next;
// 		}	
// 		while (temp_token_init != NULL && temp_token_init->type != PIPE)
// 		{
// 			printf("TOKEN IN PIPE %d\n", i);
// 			printf("2: %s\n", temp_token_init->value);
// 			temp_token = temp_token_init;

// 			// temp_pipe->token = add_back_token_in_pipe(temp_pipe->token, temp_token_init);

// 			printf("%s\n", temp_token->value);
// 			// printf("prev: %s\n", temp_pipe->prev->token->value);
// 			temp_token_init = temp_token_init->next;
// 			temp_token = temp_token->next;
// 		}
// 		i++;
// 		if (temp_token_init != NULL)
// 			temp_token_init = temp_token_init->next;
// 		if (temp_pipe)
// 			temp_pipe = temp_pipe->next; //normalement pas obligatoire
// 	}
// 	// printf("pipe_final: %s\n", sh->pipe_lst->prev->token->value);
// 	// printf("pipe final: %s\n", sh->token_lst->value);
	
// 	// while (temp_token_init->prev)
// 	// {
// 	// 	// printf("pipe final: %s\n", sh->token_lst->value);
// 	// }
// 	// sh->token_lst = sh->token_lst->prev;
// 	// printf("pipe final: %s\n", sh->token_lst->prev->value);
// }