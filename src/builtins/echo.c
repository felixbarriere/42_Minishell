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

void	print_args_2(char **args, int args_number, int type)
{
	int	i;

	i = 2;
	while (args[i])
	{
		if (type == ARG)
		{
			ft_putstr_fd(args[i], 1);
			if (i + 1 < args_number)
				ft_putchar_fd(' ', 1);
		}
		i++;
	}
}

void	print_args(char **args, int args_number)
{
	int	i;

	i = 1;
	while (args[i])
	{
		ft_putstr_fd(args[i], 1);
		if (i + 1 < args_number)
			ft_putchar_fd(' ', 1);
		i++;
	}
	ft_putchar_fd('\n', 1);
}

void	echo_command(t_pipe	*pipe)
{
	int	i;
	int	args_number;

	i = 0;
	args_number = 0;
	while (pipe->args[i])
	{
		args_number++;
		i++;
	}
	if (pipe->token->next != NULL)
	{
		if (ft_strcmp(pipe->token->next->value, "-n"))
			print_args(pipe->args, args_number);
		else
			print_args_2(pipe->args, args_number, pipe->token->next->type);
	}
	else
		ft_putstr_fd("\n", 2);
}
