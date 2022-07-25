/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccalas <ccalas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 14:57:13 by fbarrier          #+#    #+#             */
/*   Updated: 2022/07/25 11:37:39 by ccalas           ###   ########.fr       */
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

char	*ft_strjoin_path(char *s1, char *s2)
{
	char	*dest;

	if (!s1)
	{
		s1 = malloc(sizeof(char) * 1);
		s1[0] = '\0';
	}
	if (!s2)
	{
		s2 = malloc(sizeof(char) * 1);
		s2[0] = '\0';
	}
	dest = ft_calloc(sizeof(char), (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!dest)
		return (NULL);
	dest = ft_strjoin_path_2(dest, s1, s2);
	return (dest);
}
