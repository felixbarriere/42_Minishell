/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarrier <fbarrier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 17:20:48 by ccalas            #+#    #+#             */
/*   Updated: 2022/07/14 14:45:10 by fbarrier         ###   ########.fr       */
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
	printf("test\n");
	while (sh->prompt[i])
	{
		ft_find_quote_state(sh, i);
		i++;
	}
	printf("test 2\n");
	if (sh->state_quote != DEFAULT)
		return (FAILURE);
	return (SUCCESS);
}
