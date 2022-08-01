/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccalas <ccalas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 18:19:33 by fbarrier          #+#    #+#             */
/*   Updated: 2022/08/01 18:20:26 by ccalas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/minishell_d.h"
#include "../../include/minishell_f.h"
#include "../../include/minishell_s.h"

void	exit_command_2(t_sh *sh, t_pipe *pipe_lst)
{
	(void)pipe_lst;
	ft_close2();
	free_free_all(sh);
	if (sh->exit)
		exit(sh->exit);
	else
		exit(0);
}

unsigned long long	ft_long_atoi(const char *str)
{
	int						i;
	unsigned long long		nb;

	i = 0;
	nb = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		nb = nb * 10 + (str[i] - 48);
		i++;
	}
	return (nb);
}

int	too_many_chars(char *str)
{
	if (str[0] == '-')
	{
		if (check_min(str) == 0)
			return (1);
	}
	else
	{
		if (str[0] == '+')
		{
			if (ft_long_atoi(str) > 9223372036854775807)
				return (1);
		}
		else
		{
			if (check_max(str) == 0)
				return (1);
		}
	}
	return (0);
}

void	exit_error(t_token *temp, t_sh *sh, char *exit_nbr)
{
	if (!is_in_range(temp->next->value) || too_many_chars(exit_nbr))
	{
		ft_putstr_fd("exit: ", 2);
		ft_putstr_fd(temp->next->value, 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		sh->exit = 2;
	}
	if ((ft_atoi(temp->next->value) < 0 && !too_many_chars(exit_nbr)))
	{
		sh->exit = 2;
		return ;
	}
}

void	exit_command(t_sh *sh, t_pipe *pipe_lst)
{
	t_token	*temp;

	temp = pipe_lst->token;
	while (temp && temp->type != CMD)
		temp = temp->next;
	if (temp)
	{
		if (nb_pipe(sh->pipe_lst) == 0)
			ft_putstr_fd("exit\n", 1);
		if (temp->next && temp->next->type == ARG)
		{
			if (is_in_range(temp->next->value) && !temp->next->next
				&& !too_many_chars(temp->next->value))
					sh->exit = ft_atoi(temp->next->value);
			else if (temp->next->next && is_in_range(temp->next->value))
			{
				ft_putstr_fd("exit: too many arguments\n", 2);
				sh->exit = 1;
				return ;
			}
			else
				exit_error(temp, sh, temp->next->value);
		}
		exit_command_2(sh, pipe_lst);
	}
}
