/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccalas <ccalas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 18:02:57 by ccalas            #+#    #+#             */
/*   Updated: 2022/04/12 18:03:10 by ccalas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/minishell_d.h"
#include "../include/minishell_f.h"
#include "../include/minishell_s.h"

int	isin_charset(char c)
{
	if (c == '|' || c == '<' || c == '>')
		return (1);
	return (0);
}

int	isonly_space(char *str)
{
	int i = 0;

	while (str[i])
	{
		if (str[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

int	ft_parse_red(t_sh *sh)
{
	int	sec;

	sec = 0;
	if ((sh->prompt[sh->p_index] == RED_LEFT || sh->prompt[sh->p_index] == RED_RIGHT) && sh->prompt[sh->p_index + 1]) //sert à vérifier si il y a 2 '<' ou 2 '>' qui s'enchainent
	{
		if (sh->prompt[sh->p_index + 1] == RED_LEFT)
		{
			sec = RED_LEFT;
			sh->p_index++;
		}
		else if (sh->prompt[sh->p_index + 1] == RED_RIGHT)
		{
			sec = RED_RIGHT;
			sh->p_index++;
		}
	}
	return (sec);
}