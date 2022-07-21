/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccalas <ccalas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 14:57:13 by fbarrier          #+#    #+#             */
/*   Updated: 2022/07/21 17:16:44 by ccalas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/minishell_d.h"
#include "../../include/minishell_f.h"
#include "../../include/minishell_s.h"

void	ft_close(t_sh *sh, int nb_pipes)
{
	t_pipe	*start;
	int		i;

	start = sh->pipe_lst;
	i = 0;
	while (i < nb_pipes)
	{
		close(start->fd[0]);
		close(start->fd[1]);
		start = start->next;
		i++;
	}
}

void	ft_switch(t_pipe *start, int k)
{
	if (start->cmd_verified != NULL)
	{	
		if (!k)
			dup2(start->fd[1], start->output);
		else if (k && !start->next)
			dup2(start->prev->fd[0], start->input);
		else if (k && start->next)
		{
			dup2(start->prev->fd[0], start->input);
			dup2(start->fd[1], start->output);
		}
	}
}

char	*ft_strjoin_path_2(char *dest, char *s1, char *s2)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (s1[i] != '\0')
	{
		dest[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
	{
		dest[i] = s2[j];
		j++;
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
