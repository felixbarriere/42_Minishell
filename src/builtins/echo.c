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
	int	i;
	int	args_number;

	printf("commande: %s\n", pipe->cmd);

	i = 0;
	args_number = 0;
	while (pipe->args[i])
	{
		args_number++;
		i++;
	}
	printf("args_nbr: %d\n", args_number);
	if (pipe->token->next != NULL)
	{
		if (ft_strcmp(pipe->token->next->value, "-n"))
		{
			i = 1;
			while (pipe->args[i])
			{
				ft_putstr_fd(pipe->args[i], 1);
				if (i + 1 < args_number)
					ft_putchar_fd(' ', 1);
				i++;
			}
			ft_putchar_fd('\n', 1);
		}
		else
		{
			i = 2;
			while (pipe->args[i])
			{
				ft_putstr_fd(pipe->args[i], 1);
				if (i + 1 < args_number)
					ft_putchar_fd(' ', 1);
				i++;
			}			
// 			if (pipe->token->next->type == ARG)
// 			{
// 				to_print = pipe->token->next->value;
// 			// printf("commande: %s\n", pipe->token->value);
// 			// printf("echo à imprimer: %s\n", pipe->token->next->value);
// 				ft_putstr_fd(to_print, 1);
// 				ft_putchar_fd('\n', 1);
// 			}
		}
		// else
		// {
		// 	// printf("echo à imprimer: %s\n",  pipe->token->next->next->value);
		// 	to_print = pipe->token->next->next->value;
		// 	ft_putstr_fd(to_print, 1);
		// }
	}
	else
		ft_putstr_fd("\n", 2);
}

// attention plusieurs cas d'invalid read avec $USER + autres args 
// ou lorsque plusieurs appels a $USER (a regarder dans le parsing).
