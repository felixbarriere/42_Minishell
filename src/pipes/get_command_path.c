/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_command_path.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccalas <ccalas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 15:27:17 by fbarrier          #+#    #+#             */
/*   Updated: 2022/07/21 17:52:51 by ccalas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/minishell_d.h"
#include "../../include/minishell_f.h"
#include "../../include/minishell_s.h"

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

int	com_line_path(char **path, char *cmd)
{
	// int		i;

	(void)path;
	// i = 0;
	// while (path[i] && cmd != NULL)
	// {
		if (access(cmd, F_OK) == 0)
			return (1);
	// 	i++;
	// }
	return (0);
}

char	*com_line(char **path, char *cmd)
{
	char	*path_slash;
	char	*path_complete;
	int		i;

	path_slash = NULL;
	path_complete = NULL;
	i = 0;
	while (path[i] && cmd != NULL)
	{
		path_slash = ft_strjoin_path(path[i], "/");
		path_complete = ft_strjoin_path(path_slash, cmd);
		free(path_slash);
		if (access(path_complete, F_OK) == 0)
			return (path_complete);
		free(path_complete);
		i++;
	}
	return (NULL);
}

char	*get_exec(char *cmd)
{
	char	path[256];
	char	*exec;
	char	*exec_2;

	exec = NULL;
	getcwd(path, sizeof(path));
	exec = ft_substr(cmd, 1, ft_strlen(cmd) -1);
	exec_2 = ft_strjoin_path(path, exec);
	free(exec);
	return (exec_2);
}

void	get_command_path(t_sh	*sh)
{
	t_pipe	*temp;
	char	*executable;

	temp = sh->pipe_lst;
	while (sh->path != NULL && sh->pipe_lst)
	{
		if (sh->pipe_lst->cmd == NULL)
		{
			sh->pipe_lst = sh->pipe_lst->next;
			continue ;	
		}
		if (com_line_path(sh->path, sh->pipe_lst->cmd) == 1)
			sh->pipe_lst->cmd_verified = ft_strdup(sh->pipe_lst->cmd);
		else
			sh->pipe_lst->cmd_verified = com_line(sh->path, sh->pipe_lst->cmd);
		if (sh->pipe_lst->cmd_verified == NULL)
		{
			if (sh->pipe_lst->cmd
				&& ft_strncmp(sh->pipe_lst->cmd, "./", 2) == 0)
			{
				executable = get_exec(sh->pipe_lst->cmd);
				sh->pipe_lst->cmd_verified = ft_strdup(executable);
				free(executable);
			}
		}
		sh->pipe_lst = sh->pipe_lst->next;
	}
	sh->pipe_lst = temp;
}
