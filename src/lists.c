/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccalas <ccalas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 18:18:11 by ccalas            #+#    #+#             */
/*   Updated: 2022/04/29 14:43:21 by ccalas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/minishell_d.h"
#include "../include/minishell_f.h"
#include "../include/minishell_s.h"

t_token	*create_token(t_token_type type, char *value)
{
	t_token	*elem;

	elem = ft_calloc(1, sizeof(t_token));
	if (!elem)
		return (NULL);
	elem->type = type;
	elem->value = value;
	elem->next = NULL;
	//TEST
	elem->prev = NULL;
	return (elem);
}

t_token	*add_back_token(t_token *list, t_token_type type, char *value)
{
	t_token *new;
	t_token	*tmp;

	new = create_token(type, value);
	if (!new)
		return NULL;
	if (!list)
		return (new);
	else
	{
		tmp = list;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
		//TEST
		new->prev = tmp;
	}
	return (list);
}

void print_tokens(t_token *li)
{
	while(li != NULL)
	{
		printf("\n");
		printf("[%s] ", li->value);
		printf("[Type : %d]\n", li->type);
		if (li->prev)
			printf("[precedent = %s]", li->prev->value);
		if  (li->next)
			printf("[suivant = %s]", li->next->value);
		li = li->next;
	}
	printf("\n");
}

int list_length(t_token *li)
{
	int size = 0;

	while(li != NULL)
	{
		size++;
		li = li->next;
	}
	return size;
}

void	ft_set_null_free_elem(t_token *elem)
{
	if (!elem)
		return ;
	elem->value = NULL;
	elem->next = NULL;
	free(elem);
}

void	ft_set_null_free_list(t_token **a_list)
{
	t_token	*tmp;

	if (!(*a_list))
		return ;
	while (*a_list)
	{
		tmp = (*a_list)->next;
		ft_set_null_free_elem(*a_list);
		*a_list = tmp;
	}
}