/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarrier <fbarrier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 17:12:23 by fbarrier          #+#    #+#             */
/*   Updated: 2022/06/23 16:10:37 by fbarrier         ###   ########.fr       */
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
	while(sh->env[i])
	{
		if (!ft_strncmp(sh->env[i], "OLDPWD", 6))
		{
			// printf("char ** OLDPWD: %s\n", sh->env[i]);
			free(sh->env[i]);
			sh->env[i] = ft_strdup("OLDPWD=");
			sh->env[i] = ft_strjoin(sh->env[i], old_path);
			// printf("char ** OLDPWD2: %s\n", sh->env[i]);
		}
		i++;
	}
}

void	change_pwd_array(t_sh	*sh, char *path)
{
	int	i;
	
	i = 0;
	while(sh->env[i])
	{
		if (!ft_strncmp(sh->env[i], "PWD", 3))
		{
			// printf("char ** PWD: %s\n", sh->env[i]);
			free(sh->env[i]);
			sh->env[i] = ft_strdup("PWD=");
			sh->env[i] = ft_strjoin(sh->env[i], path);
			// printf("char ** PWD2: %s\n", sh->env[i]);
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
			break;
		}
		sh->env_lst = sh->env_lst->next;
	}
	// printf("pwd_key2: %s\n", sh->env_lst->key);
	printf("pwd_value2: %s\n", sh->env_lst->value);
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
			break;
		}
		sh->env_lst = sh->env_lst->next;
	}
	// printf("old_pwd_key2: %s\n", sh->env_lst->key);
	printf("old_pwd_value2: %s\n", sh->env_lst->value);
	change_old_pwd_array(sh, old_path);
	sh->env_lst = start;
}

void	cd_command(t_sh *sh)
{
	char	*wrong_path;
	char	old_path[256];
	char	path[256];

	getcwd(old_path, sizeof(old_path));
	printf("commande: %s\n", sh->pipe_lst->cmd);
	printf("options: %s\n", sh->pipe_lst->options); //comment retrouver les options? token?
	if (sh->pipe_lst->token->next != NULL)
	{
		if (chdir(sh->pipe_lst->token->next->value) == -1)
		{
			wrong_path = sh->pipe_lst->token->next->value;
			ft_putstr_fd("cd: no such file or directory: ", 2);
			g_sh.exit = 1;
			ft_putstr_fd(wrong_path, 2);
			ft_putchar_fd('\n', 2);
		}
		else
		{
			getcwd(path, sizeof(path));
			change_old_pwd(sh, old_path);
			change_pwd(sh, path);
		}
	}
	else 
		ft_putstr_fd("cd: no path\n", 2);
}