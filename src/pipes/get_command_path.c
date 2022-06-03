/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_command_path.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarrier <fbarrier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 15:27:17 by fbarrier          #+#    #+#             */
/*   Updated: 2022/06/03 16:48:58 by fbarrier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/minishell_d.h"
#include "../../include/minishell_f.h"
#include "../../include/minishell_s.h"

char	*ft_strjoin_path(char *s1, char *s2)
{
	char	*dest;
	int		i;
	int		j;

	i = 0;
	j = 0;
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
	// free(s1);
	// free(s2);
	return (dest);
}

char	*command_line(char **path, char *cmd)
{
	char	*path_slash;
	char	*path_complete;
	// int		*cmd_bin;
	// (void)cmd;
	int		i;

	path_slash = NULL;
	path_complete = NULL;
	i = 0;
	while (path[i])
	{
		path_slash = ft_strjoin_path(path[i], "/");
		path_complete = ft_strjoin_path(path_slash, cmd); //a free
		printf("path complete: %s\n", path_complete);
		if (access(path_complete, F_OK) == 0)
			return (path_complete);
		free(path_slash);
		free(path_complete);
		i++;
	}
	return (NULL);
}

void	get_command_path(t_sh	*sh)
{
	int	i;
	// (void)sh;
	// data->cmd = command_line(data->cmd_binaries, data->cmd_av[0]);
	i = 0;
	while(sh->pipe_lst)
	{
		sh->pipe_lst->cmd_verified = command_line(sh->path, sh->pipe_lst->cmd);
		printf("cmd_verified: %s\n", sh->pipe_lst->cmd_verified);
		sh->pipe_lst = sh->pipe_lst->next;
	}
	// printf("commande complete: %s\n", sh->pipe_lst->cmd_verified);
}