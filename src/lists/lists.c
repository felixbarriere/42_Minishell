/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccalas <ccalas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 18:18:11 by ccalas            #+#    #+#             */
/*   Updated: 2022/05/31 15:57:30 by ccalas           ###   ########.fr       */
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
		// if (li->prev)
		// 	printf("[precedent = %s]", li->prev->value);
		// if  (li->next)
		// 	printf("[suivant = %s]", li->next->value);
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
			{
			printf("TOKEN TYPE = %u et TOKEN VALUE = %s\n", lst->type, lst->value);	
				return (SUCCESS);
			}
		}
		lst = lst->next;
	}
	return (FAILURE);
}
// /*---------------------------------------------------------------------*/
// /**
// * Supprime un entier de la tête de la Liste
// * @param li La liste
// * @return La liste sans l'élément retiré
// */
// t_token *pop_front_list(t_token *li)
// {
// 	t_token *element;

// 	element = malloc(sizeof(*element));

// 	if(element == NULL)
// 	{
// 		fprintf(stderr, "Erreur : probleme allocation dynamique.\n");
// 		exit(EXIT_FAILURE);
// 	}

// 	if(is_empty_list(li))
// 		return (new_list());

// 	element = li->next;

// 	free(li);
// 	li = NULL;
// 	return (element);
// }

// /*---------------------------------------------------------------------*/
// /**
// * Supprime tous les éléments d'une Liste
// * @param li La liste
// * @return Une Liste vide
// */
// void clear_list(t_token *li)
// {
// 	if(is_empty_list(li))
// 		return ;

// 	while(li != NULL)
// 		li = pop_front_list(li);
// }

// t_env *pop_front_list_env(t_env *li)
// {
// 	t_env *element;

// 	element = malloc(sizeof(*element));

// 	if(element == NULL)
// 	{
// 		fprintf(stderr, "Erreur : probleme allocation dynamique.\n");
// 		exit(EXIT_FAILURE);
// 	}

// 	if(is_empty_list_env(li))
// 		return (new_list_env());

// 	element = li->next;

// 	free(li);
// 	li = NULL;
// 	return (element);
// }

// void clear_list_env(t_env *li)
// {
// 	if(is_empty_list_env(li))
// 		return ;

// 	while(li != NULL)
// 		li = pop_front_list_env(li);
// }
