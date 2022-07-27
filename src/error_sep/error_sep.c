/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_sep.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccalas <ccalas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 18:20:05 by fbarrier          #+#    #+#             */
/*   Updated: 2022/07/26 13:52:19 by fbarrier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/minishell_d.h"
#include "../../include/minishell_f.h"
#include "../../include/minishell_s.h"

extern t_sh	g_sh;

bool	is_type(t_token *current, t_token_type type)
{
	if (current == NULL && type == BLANK)
		return (true);
	else if (current != NULL && current->type == type)
		return (true);
	return (false);
}

int	check_error_sep_0(t_token *token_lst)
{
	if ((is_type(token_lst->prev, R_RIGHT) && is_type(token_lst, PIPE)
			&& is_type(token_lst->next, PIPE))
		|| (is_type(token_lst, R_LEFT) && is_type(token_lst->next, PIPE))
		|| (is_type(token_lst, R_RIGHT) && is_type(token_lst->next, PIPE))
		|| (is_type(token_lst, PIPE) && is_type(token_lst->next, PIPE))
		|| (is_type(token_lst->prev, BLANK) && is_type(token_lst, PIPE))
		|| (is_type(token_lst, PIPE) && is_type(token_lst->next, BLANK)))
	{
		ft_putstr_fd("syntax error near unexpected token  `|'\n", 2);
		g_sh.exit = 2;
		return (FAILURE);
	}
	else if (is_type(token_lst->prev, DR_RIGHT) && is_type(token_lst, PIPE)
		&& is_type(token_lst->next, PIPE))
	{
		ft_putstr_fd("syntax error near unexpected token  `||'\n", 2);
		g_sh.exit = 2;
		return (FAILURE);
	}
	return (SUCCESS);
}

int	check_error_sep_1(t_token *token_lst)
{
	if ((is_type(token_lst, R_LEFT) && is_type(token_lst->next, R_LEFT))
		|| (is_type(token_lst, DR_RIGHT) && is_type(token_lst->next, R_LEFT))
		|| (is_type(token_lst, DR_LEFT) && is_type(token_lst->next, R_LEFT))
		|| (is_type(token_lst, R_RIGHT) && is_type(token_lst->next, R_LEFT)))
	{
		g_sh.exit = 2;
		ft_putstr_fd("syntax error near unexpected token `<'\n", 2);
		return (FAILURE);
	}
	return (SUCCESS);
}

int	check_error_sep_2(t_token *token_lst)
{
	if ((is_type(token_lst, R_LEFT) && is_type(token_lst->next, R_RIGHT))
		|| (is_type(token_lst, DR_LEFT) && is_type(token_lst->next, R_RIGHT))
		|| (is_type(token_lst, R_RIGHT) && is_type(token_lst->next, R_RIGHT))
		|| (is_type(token_lst, DR_RIGHT) && is_type(token_lst->next, R_RIGHT)))
	{
		g_sh.exit = 2;
		ft_putstr_fd("syntax error near unexpected token `>'\n", 2);
		return (FAILURE);
	}
	return (SUCCESS);
}

int	check_error_sep(t_token *token_lst)
{
	while (token_lst)
	{
		if (check_error_sep_5(token_lst) == FAILURE)
			return (FAILURE);
		else if (check_error_sep_0(token_lst) == FAILURE)
			return (FAILURE);
		else if (check_error_sep_6(token_lst) == FAILURE)
			return (FAILURE);
		else if (check_error_sep_1(token_lst) == FAILURE)
			return (FAILURE);
		else if (check_error_sep_2(token_lst) == FAILURE)
			return (FAILURE);
		else if (check_error_sep_3(token_lst) == FAILURE)
			return (FAILURE);
		else if (check_error_sep_4(token_lst) == FAILURE)
			return (FAILURE);
		token_lst = token_lst->next;
	}
	return (SUCCESS);
}
