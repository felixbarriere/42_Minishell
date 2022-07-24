/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 18:19:33 by fbarrier          #+#    #+#             */
/*   Updated: 2022/07/24 21:14:39 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/minishell_d.h"
#include "../../include/minishell_f.h"
#include "../../include/minishell_s.h"

void	exit_command_2(t_sh *sh, t_pipe *pipe_lst)
{
	if (sh->path != NULL)
		ft_free(sh->path);
	ft_free(sh->env);
	clear_list(sh->token_lst);
	clear_list_pipe(pipe_lst);
	if (sh->exit)
		exit(sh->exit);
	else
		exit(2);
}

int	is_in_range(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_isdigit(str[i]) == 1 || (i == 0 && str[i] == '-'))
			i++;
		else
			return (0);
	}
	return (1);
}

unsigned long long	ft_long_atoi(const char *str)
{
	int						i;
	// int						sign;
	unsigned long long	nb;

	i = 0;
	// sign = 1;
	nb = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		// if (str[i] == '-')
		// 	sign *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		nb = nb * 10 + (str[i] - 48);
		i++;
	}
	// * sign;
	return (nb);
}

// static int	check_max(char *str)
// {
// 	char	*max;
// 	int		i;

// 	while (*str == '0')
// 		str++;
// 	if (!*str)
// 		return (0);
// 	if (ft_strlen(str) > 19)
// 		return (0);
// 	if (ft_strlen(str) < 19)
// 		return (1);
// 	max = ft_strdup("9223372036854775807");
// 	if (!max)
// 		return (1);
// 	i = 0;
// 	while (max[i])
// 	{
// 		if (str[i] > max[i])
// 			return (free(max), 0);
// 		if (str[i] < max[i])
// 			return (free(max), 1);
// 		i++;
// 	}
// 	return (free(max), 1);
// }

char	*delete_neg(char *str)
{
	int		i;
	int		j;
	char	*str_2;

	i = 1;
	j = 0;
	str_2 = NULL;
	if (str[0] == '-')
	{
		str_2 = malloc(sizeof(char) * ft_strlen(str));
		if (!str)
			return NULL;
		while (str[i])
		{

			str_2[j] = str[i];
			j++;
			i++;
		}
		str_2[j] = '\0';
		return (str_2);
	}
	return (str);
}

int	too_many_chars(char *str)
{
	printf("ft_long_atoi(str): %lld \n", ft_long_atoi(str));
	printf("str: %s \n", str);
	printf("ft_atoi(str): %d \n", ft_atoi(str));
	if (ft_atoi(str) < 0)
	{
		printf("test\n");
		printf("ft_long_atoi(str): %lld \n", ft_long_atoi(str));
		printf("str: %s \n", str);
		str = delete_neg(str);
		printf("ft_long_atoi(str): %lld \n", ft_long_atoi(str));
		printf("str: %s \n", str);
		printf("test2\n");
		if (ft_long_atoi(str) > 9223372036854775808)
		{
			free (str);
			return (1);
		}
	}
	else if (ft_long_atoi(str) > 9223372036854775807 )
		return (1);
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
	if ((ft_atoi(temp->next->value) < 0 && !too_many_chars(exit_nbr))
		|| ft_atoi(temp->next->value) >= 255) // creer un atoll?
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
		ft_putstr_fd("exit\n", 1);
		if (temp->next && temp->next->type == ARG)
		{
			if (is_in_range(temp->next->value) && ft_atoi(temp->next->value)
				<= 255 && !temp->next->next
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

// CASES
// exit hh jj:doit qd meme exit
// exit hhh 45 34: doit qd meme sortir
// exit 22222222222222222222222 (20 chiffres): nu;eric argument required

// void	exit_command(t_sh *sh)
// {
// 	char	*exit_nbr;

// 	if (sh->pipe_lst->token->next)
// 	{
// 		exit_nbr = sh->pipe_lst->token->next->value;
// 		if (exit_nbr && is_in_range(exit_nbr) && ft_atoi(exit_nbr) <= 255
// 			&& !sh->pipe_lst->token->next->next)
// 			sh->exit = ft_atoi(exit_nbr);
// 		else
// 		{
// 			ft_putstr_fd("exit: bad argument\n", 2);
// 			return ;
// 		}
// 	}
// 	if (sh->path != NULL)
// 	{
// 		printf("sh->path existe\n");
// 		ft_free(sh->path);
// 	}
// 	ft_free(sh->env);
// 	clear_list(sh->token_lst);
// 	clear_list_pipe(sh->pipe_lst);
// 	if (sh->exit)
// 	{
// 			printf("ICI\n");
// 			exit(sh->exit);
// 	}
// 		else
// 		{
// 			printf("ICI 2\n");
// 			exit(2);
// 		}
// }
