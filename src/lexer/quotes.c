/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 17:20:48 by ccalas            #+#    #+#             */
/*   Updated: 2022/07/17 15:52:46 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/minishell_d.h"
#include "../../include/minishell_f.h"
#include "../../include/minishell_s.h"

void	ft_find_quote_state(t_sh *sh, int i)
{
	if (sh->prompt[i] == SIMPLE && sh->state_quote == DEFAULT)
		sh->state_quote = SIMPLE;
	else if (sh->prompt[i] == DOUBLE && sh->state_quote == DEFAULT)
		sh->state_quote = DOUBLE;
	else if (sh->prompt[i] == SIMPLE && sh->state_quote == SIMPLE)
		sh->state_quote = DEFAULT;
	else if (sh->prompt[i] == DOUBLE && sh->state_quote == DOUBLE)
		sh->state_quote = DEFAULT;
}

int	ft_is_quote_ok(t_sh *sh)
{
	int	i;

	i = 0;
	while (sh->prompt[i])
	{
		ft_find_quote_state(sh, i);
		i++;
	}
	if (sh->state_quote != DEFAULT)
		return (FAILURE);
	return (SUCCESS);
}
