/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_sep2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccalas <ccalas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 18:25:05 by fbarrier          #+#    #+#             */
/*   Updated: 2022/07/09 12:15:44 by ccalas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/minishell_d.h"
#include "../../include/minishell_f.h"
#include "../../include/minishell_s.h"

extern t_sh	g_sh;

int	check_error_sep_3(t_token *token_lst)
{
	if ((is_type(token_lst, R_LEFT) && is_type(token_lst->next, DR_LEFT))
		|| (is_type(token_lst, DR_LEFT) && is_type(token_lst->next, DR_LEFT))
		|| (is_type(token_lst, R_RIGHT) && is_type(token_lst->next, DR_LEFT))
		|| (is_type(token_lst, DR_RIGHT) && is_type(token_lst->next, DR_LEFT)))
	{
		g_sh.exit = 2;
		ft_putstr_fd("syntax error near unexpected token `<<'\n", 2);
		return (FAILURE);
	}
	return (SUCCESS);
}

int	check_error_sep_4(t_token *token_lst)
{
	if ((is_type(token_lst, R_LEFT) && is_type(token_lst->next, DR_RIGHT))
		|| (is_type(token_lst, DR_LEFT) && is_type(token_lst->next, DR_RIGHT))
		|| (is_type(token_lst, R_RIGHT) && is_type(token_lst->next, DR_RIGHT))
		|| (is_type(token_lst, DR_RIGHT) && is_type(token_lst->next, DR_RIGHT)))
	{
		g_sh.exit = 2;
		ft_putstr_fd("syntax error near unexpected token `>>'\n", 2);
		return (FAILURE);
	}
	return (SUCCESS);
}

int	check_error_sep_5(t_token *token_lst)
{
	if ((is_type(token_lst->prev, BLANK) && is_type(token_lst, R_LEFT)
			&& is_type(token_lst->next, BLANK))
		|| (is_type(token_lst->prev, BLANK) && is_type(token_lst, DR_LEFT)
			&& is_type(token_lst->next, BLANK))
		|| (is_type(token_lst->prev, BLANK) && is_type(token_lst, R_RIGHT)
			&& is_type(token_lst->next, BLANK))
		|| (is_type(token_lst->prev, BLANK) && is_type(token_lst, DR_RIGHT)
			&& is_type(token_lst->next, BLANK)))
	{
		g_sh.exit = 2;
		ft_putstr_fd("syntax error near unexpected token `newline'\n", 2);
		return (FAILURE);
	}
	else if (is_type(token_lst->prev, BLANK) && is_type(token_lst, PIPE)
		&& is_type(token_lst->next, BLANK))
	{
		g_sh.exit = 2;
		ft_putstr_fd("syntax error near unexpected token `|'\n", 2);
		return (FAILURE);
	}
	return (SUCCESS);
}

int	check_error_sep_6(t_token *token_lst)
{
	if ((is_type(token_lst->prev, STR) && is_type(token_lst, R_LEFT)
			&& is_type(token_lst->next, BLANK))
		|| (is_type(token_lst->prev, STR) && is_type(token_lst, DR_LEFT)
			&& is_type(token_lst->next, BLANK))
		|| (is_type(token_lst->prev, STR) && is_type(token_lst, R_RIGHT)
			&& is_type(token_lst->next, BLANK))
		|| (is_type(token_lst->prev, STR) && is_type(token_lst, DR_RIGHT)
			&& is_type(token_lst->next, BLANK))
		|| (is_type(token_lst, R_LEFT) && is_type(token_lst->next, BLANK)))
	{
		g_sh.exit = 2;
		ft_putstr_fd("syntax error near unexpected token `newline'\n", 2);
		return (FAILURE);
	}
	return (SUCCESS);
}
