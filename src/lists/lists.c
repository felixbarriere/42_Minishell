/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarrier <fbarrier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 18:18:11 by ccalas            #+#    #+#             */
/*   Updated: 2022/06/24 12:30:45 by fbarrier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/minishell_d.h"
#include "../../include/minishell_f.h"
#include "../../include/minishell_s.h"

t_token	*create_token(t_token_type type, char *value)
{
	t_token	*elem;

	elem = ft_calloc(1, sizeof(t_token));
	if (!elem)
		return (NULL);
	elem->type = type;
	elem->value = value;
	elem->next = NULL;
	elem->prev = NULL;
	return (elem);
}

t_token	*add_back_token(t_token *list, t_token_type type, char *value)
{
	t_token	*new;
	t_token	*tmp;

	new = create_token(type, value);
	if (!new)
		return (NULL);
	if (!list)
		return (new);
	else
	{
		tmp = list;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
		new->prev = tmp;
	}
	return (list);
}

void	print_tokens(t_token *li)
{
	while (li != NULL)
	{
		printf("\n");
		printf("[%s] ", li->value);
		printf("[Type : %d]\n", li->type);
		li = li->next;
	}
	printf("\n");
}

int	list_length(t_token *li)
{
	int	size;

	size = 0;
	while (li != NULL)
	{
		size++;
		li = li->next;
	}
	return (size);
}

int	ft_lstlast_dr_left(t_token *lst)
{
	if (!lst)
		return (FAILURE);
	while (lst)
	{
		if (lst->next == NULL)
		{
			if (lst->type == DR_LEFT)
				return (SUCCESS);
		}
		lst = lst->next;
	}
	return (FAILURE);
}
