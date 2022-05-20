/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarrier <fbarrier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 18:18:11 by ccalas            #+#    #+#             */
/*   Updated: 2022/05/20 18:25:23 by fbarrier         ###   ########.fr       */
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
		// if (li->prev)
		// 	printf("[precedent = %s]", li->prev->value);
		// if  (li->next)
		// 	printf("[suivant = %s]", li->next->value);
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

/*---------------------------------------------------------------------*/
/* Retourne une nouvelle Liste
* @return Une liste vide
*/
t_token *new_list(void)
{
	return NULL;
}

t_env *new_list_env(void)
{
	return NULL;
}


/**
* Vérifie si une List est vide
* @param li La liste à tester
* @return true si elle est vide, faux sinon
*/
bool is_empty_list(t_token  *li)
{
	if(li == NULL)
		return true;

	return false;
}

bool is_empty_list_env(t_env  *li)
{
	if(li == NULL)
		return true;

	return false;
}

/*---------------------------------------------------------------------*/
/**
* Supprime un entier de la tête de la Liste
* @param li La liste
* @return La liste sans l'élément retiré
*/
t_token *pop_front_list(t_token *li)
{
	t_token *element;

	element = malloc(sizeof(*element));

	if(element == NULL)
	{
		fprintf(stderr, "Erreur : probleme allocation dynamique.\n");
		exit(EXIT_FAILURE);
	}

	if(is_empty_list(li))
		return (new_list());

	element = li->next;

	free(li);
	li = NULL;
	return (element);
}

/*---------------------------------------------------------------------*/
/**
* Supprime tous les éléments d'une Liste
* @param li La liste
* @return Une Liste vide
*/
void clear_list(t_token *li)
{
	if(is_empty_list(li))
		return ;

	while(li != NULL)
		li = pop_front_list(li);
}

t_env *pop_front_list_env(t_env *li)
{
	t_env *element;

	element = malloc(sizeof(*element));

	if(element == NULL)
	{
		fprintf(stderr, "Erreur : probleme allocation dynamique.\n");
		exit(EXIT_FAILURE);
	}

	if(is_empty_list_env(li))
		return (new_list_env());

	element = li->next;

	free(li);
	li = NULL;
	return (element);
}

void clear_list_env(t_env *li)
{
	if(is_empty_list_env(li))
		return ;

	while(li != NULL)
		li = pop_front_list_env(li);
}