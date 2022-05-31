/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_creation.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarrier <fbarrier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 16:17:44 by fbarrier          #+#    #+#             */
/*   Updated: 2022/05/31 17:08:30 by fbarrier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/minishell_d.h"
#include "../../include/minishell_f.h"
#include "../../include/minishell_s.h"

// t_token	*ft_strdup_token(t_token *value)
// {
// 	t_token	*dest;
// 	int		i;

// 	i = 0;
// 	dest = ft_calloc(1, sizeof(t_token));
// 	if (!dest)
// 		return (NULL);
// 	dest->type = value->type;
// 	dest->value = value->value;
// 	dest->prev = value->prev;
// 	dest->next = value->next;
// 	return (dest);
// }

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
	}
	// free(new);
	// free(tmp);
	return (tmp);
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
// 	// new = create_token_in_pipe(value);
// 	printf("test value token 2: %s\n", value->value);
// 	new = value;
// 	if (!new)
// 		return (NULL);
// 	if (!list)
// 		return (new);
// 	else
// 	{
// 		tmp = list;
// 		printf("test value token 3: %s\n", tmp->value);
// 		// printf("test value token next: %s\n", tmp->next->value);
// 		// printf("test value token next next: %s\n", tmp->next->next->value);
// 		// printf("test value token next next next: %s\n", tmp->next->next->next->value);
// 		// printf("test value token next next next next: %s\n", tmp->next->next->next->next->value);
// 		// while (tmp->next != NULL)
// 		// {
// 		// 	printf("test value token 2: %s\n", tmp->value);
// 		// 	tmp = tmp->next;
// 		// }
// 		tmp->next = new;
// 	}
// 	// free(new);
// 	// free(tmp);
// 	return (list);
// }

void	pipe_creation(t_sh *sh)
{	
	// t_pipe	pipe_lst;
	int	i = 0;
	// t_token	temp_token = sh->pipe_lst->token;
	// t_pipe	temp_pipe = sh->pipe_lst;
	
	sh->pipe_lst = NULL;


	while (sh->token_lst != NULL)
	{
		if (sh->token_lst->type != PIPE)
		{
			printf("PIPE_LIST %d\n", i);
			sh->pipe_lst = add_back_pipe_token(sh->pipe_lst, sh->token_lst);
			printf("pipe: %s\n", sh->pipe_lst->token->value);
			sh->token_lst = sh->token_lst->next;

		}	
		while (sh->token_lst != NULL && sh->token_lst->type != PIPE)
		{
			printf("TOKEN IN PIPE %d\n", i);
			printf("2: %s\n", sh->token_lst->value);
			sh->pipe_lst->token = sh->token_lst;

			// sh->pipe_lst->token = add_back_token_in_pipe(sh->pipe_lst->token, sh->token_lst);
			printf("%s\n", sh->pipe_lst->token->value);
			sh->token_lst = sh->token_lst->next;
			sh->pipe_lst->token = sh->pipe_lst->token->next;
		}
		i++;
		if (sh->token_lst != NULL)
			sh->token_lst = sh->token_lst->next;
		if (sh->pipe_lst)
			sh->pipe_lst = sh->pipe_lst->next; //normalement pas obligatoire
	}
	// printf("pipe final: %s\n", sh->pipe_lst->token->value);
	// while (sh->pipe_lst->token->next)
	// {
	// 	printf("pipe final: %s\n", sh->pipe_lst->token->value);
	// 	sh->pipe_lst = sh->pipe_lst->next;
	// }
}