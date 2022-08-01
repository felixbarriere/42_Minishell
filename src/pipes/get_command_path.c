/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_command_path.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarrier <fbarrier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 15:27:17 by fbarrier          #+#    #+#             */
/*   Updated: 2022/08/01 11:14:41 by fbarrier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/minishell_d.h"
#include "../../include/minishell_f.h"
#include "../../include/minishell_s.h"

int	com_line_path(char **path, char *cmd)
{
	int		i;

	i = 0;
	while (!ft_strncmp(cmd, "/", 1) && path[i] && cmd != NULL)
	{
		if (access(cmd, F_OK) == 0)
			return (1);
		i++;
	}
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
	exec = ft_substr(cmd, 1, ft_strlen(cmd) - 1);
	exec_2 = ft_strjoin_path(path, exec);
	free(exec);
	return (exec_2);
}

void	get_command_path_2(t_pipe	*pipe_lst, t_sh *sh)
{
	char	*executable;

	if (pipe_lst->cmd_verified == NULL)
	{
		if (pipe_lst->cmd
			&& ft_strncmp(pipe_lst->cmd, "./", 2) == 0)
		{
			executable = get_exec(pipe_lst->cmd);
			pipe_lst->cmd_verified = ft_strdup(executable);
			free(executable);
			if (access(pipe_lst->cmd_verified, F_OK) != 0)
			{
				ft_putstr_fd("bash: ", 2);
				ft_putstr_fd(pipe_lst->cmd, 2);
				ft_putstr_fd(": No such file or directory\n", 2);
				sh->exit = 127;
			}	
		}
		else if (pipe_lst->cmd && ft_strncmp(pipe_lst->cmd, "../", 3) == 0)
			get_command_path_3(sh, pipe_lst);
	}
}

void	get_command_path(t_sh	*sh)
{
	t_pipe	*temp;

	temp = sh->pipe_lst;
	while (sh->pipe_lst)
	{
		if (sh->pipe_lst->cmd == NULL || !ft_strcmp(sh->pipe_lst->cmd, ""))
		{
			sh->pipe_lst = sh->pipe_lst->next;
			continue ;
		}
		if (com_line_path(sh->path, sh->pipe_lst->cmd) == 1)
			sh->pipe_lst->cmd_verified = ft_strdup(sh->pipe_lst->cmd);
		else if (sh->path != NULL)
			sh->pipe_lst->cmd_verified = com_line(sh->path, sh->pipe_lst->cmd);
		get_command_path_2(sh->pipe_lst, sh);
		sh->pipe_lst = sh->pipe_lst->next;
	}
	sh->pipe_lst = temp;
}
