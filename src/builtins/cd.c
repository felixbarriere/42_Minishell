/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarrier <fbarrier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 17:12:23 by fbarrier          #+#    #+#             */
/*   Updated: 2022/07/30 15:49:49 by fbarrier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/minishell_d.h"
#include "../../include/minishell_f.h"
#include "../../include/minishell_s.h"

extern t_sh	g_sh;

void	change_old_pwd_array(t_sh	*sh, char *old_path)
{
	int	i;

	i = 0;
	while (sh->env[i])
	{
		if (!ft_strncmp(sh->env[i], "OLDPWD", 6))
		{
			free(sh->env[i]);
			sh->env[i] = ft_strdup("OLDPWD=");
			sh->env[i] = ft_strjoin(sh->env[i], old_path);
		}
		i++;
	}
}

void	change_pwd_array(t_sh	*sh, char *path)
{
	int	i;

	i = 0;
	while (sh->env[i])
	{
		if (!ft_strncmp(sh->env[i], "PWD", 3))
		{
			free(sh->env[i]);
			sh->env[i] = ft_strdup("PWD=");
			sh->env[i] = ft_strjoin(sh->env[i], path);
		}
		i++;
	}
}

void	change_pwd(t_sh	*sh, char *path)
{
	t_env	*start;

	start = sh->env_lst;
	while (sh->env_lst != NULL)
	{
		if (!ft_strcmp(sh->env_lst->key, "PWD"))
		{
			free(sh->env_lst->value);
			sh->env_lst->value = ft_strdup(path);
			break ;
		}
		sh->env_lst = sh->env_lst->next;
	}
	change_pwd_array(sh, path);
	sh->env_lst = start;
}

void	change_old_pwd(t_sh	*sh, char *old_path)
{
	t_env	*start;

	start = sh->env_lst;
	while (sh->env_lst != NULL)
	{
		if (!ft_strcmp(sh->env_lst->key, "OLDPWD"))
		{
			free(sh->env_lst->value);
			sh->env_lst->value = ft_strdup(old_path);
			break ;
		}
		sh->env_lst = sh->env_lst->next;
	}
	change_old_pwd_array(sh, old_path);
	sh->env_lst = start;
}

void	cd_command(t_sh	*sh, t_pipe *pipe_lst)
{
	char	old_path[256];

	if (getcwd(old_path, sizeof(old_path)) != NULL
		|| !(pipe_lst->token->next))
	{
		if ((pipe_lst->token->next) && !(pipe_lst->token->next->next))
		{
			if (chdir(pipe_lst->token->next->value) == -1)
				error_cd(pipe_lst->token->next->value);
			else
				change_all_pwd(sh, old_path);
		}
		else if (!(pipe_lst->token->next))
			cd_home(sh, old_path);
		else
		{
			ft_putstr_fd("cd: too many arguments\n", 2);
			g_sh.exit = 1;
		}
	}
	else
	{
		ft_putstr_fd("chdir: error retrieving current directory\n", 2);
		g_sh.exit = 1;
	}
}
