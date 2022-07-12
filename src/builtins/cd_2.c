/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 16:47:49 by fbarrier          #+#    #+#             */
/*   Updated: 2022/07/12 19:25:45 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/minishell_d.h"
#include "../../include/minishell_f.h"
#include "../../include/minishell_s.h"

extern t_sh	g_sh;

void	error_cd(char	*bad_dir)
{
	ft_putstr_fd("cd: no such file or directory: ", 2);
	ft_putstr_fd(bad_dir, 2);
	ft_putchar_fd('\n', 2);
	g_sh.exit = 1;
}

void	cd_home(t_sh *sh, char *old_path)
{
	printf("test: %s\n", expander(sh, "HOME"));
	if (chdir(expander(sh, "HOME")) == -1)
		printf("cd supprimé?\n");
	if (getcwd(old_path, sizeof(old_path)) != NULL)
	{
		change_old_pwd(sh, old_path);
		change_pwd(sh, expander(sh, "HOME"));
	}
}

void	change_all_pwd(t_sh *sh, char *old_path)
{
	char	path[256];
		
	getcwd(path, sizeof(path));
	change_old_pwd(sh, old_path);
	change_pwd(sh, path);
}