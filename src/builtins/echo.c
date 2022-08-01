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

int	is_valid_option(char *str)
{
	if (!ft_strcmp(str, "-n"))
		return (1);
	else if (!ft_strcmp(str, "-n")
		|| (!ft_strncmp(str, "-n", 2) && only_n(str)))
		return (1);
	else
		return (0);
}

int	is_only_n_before(int index, char **args)
{
	int	i;

	i = 1;
	while (i < index)
	{
		if (!ft_strcmp(args[i], "-n")
			|| (!ft_strncmp(args[i], "-n", 2)
				&& only_n(args[i])))
			i++;
		else
			return (0);
	}
	return (1);
}

void	print_args_2(char **args, int args_number, int type)
{
	int	i;

	i = 2;
	while (args[i])
	{
		if (type == ARG)
		{
			if (!is_valid_option(args[i])
				|| (!is_only_n_before(i, args)))
				ft_putstr_fd(args[i], 1);
			if ((i + 1 < args_number) && (!is_valid_option(args[i])
					|| (!is_only_n_before(i, args))))
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

void	echo_command(t_sh	*sh, t_pipe	*pipe)
{
	int		i;
	int		args_number;

	i = 0;
	args_number = 0;
	while (pipe->args[i])
	{
		args_number++;
		i++;
	}
	if (pipe->token->next != NULL)
	{
		if (is_valid_option(pipe->token->next->value))
			print_args_2(pipe->args, args_number, pipe->token->next->type);
		else
			print_args(pipe->args, args_number);
		sh->exit = 0;
	}
	else if (nb_pipe(sh->pipe_lst) == 0)
		ft_putstr_fd("\n", 1);
	else if (nb_pipe(sh->pipe_lst) > 0 && sh->exec_pipe_k == 0)
		ft_putstr_fd(" ", 1);
	else
		ft_putstr_fd("\n", 1);
	sh->exit = 0;
}
