/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 13:45:59 by marvin            #+#    #+#             */
/*   Updated: 2022/06/15 13:45:59 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/minishell_d.h"
#include "../../include/minishell_f.h"
#include "../../include/minishell_s.h"

void	echo_command(t_pipe	*pipe)
{
	char *to_print;
	if (pipe->token->next != NULL)
	{
		if (ft_strcmp(pipe->token->next->value, "-n"))
		{
			if (pipe->token->next->type == ARG)
			{
				to_print = pipe->token->next->value;
			// printf("commande: %s\n", pipe->token->value);
			// printf("echo à imprimer: %s\n", pipe->token->next->value);
				ft_putstr_fd(to_print, 1);
				ft_putchar_fd('\n', 1);
			}
		}
		else
		{
			// printf("echo à imprimer: %s\n",  pipe->token->next->next->value);
			to_print = pipe->token->next->next->value;
			ft_putstr_fd(to_print, 1);
		}
	}
	else
		ft_putstr_fd("\n", 2);
}

// attention plusieurs cas d'erreur avec $USER + autres args 
// cas plusieur args pas gere