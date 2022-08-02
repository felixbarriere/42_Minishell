/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_command_path_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccalas <ccalas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 19:12:18 by fbarrier          #+#    #+#             */
/*   Updated: 2022/08/02 12:51:15 by ccalas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/minishell_d.h"
#include "../../include/minishell_f.h"
#include "../../include/minishell_s.h"

char	*get_exec_relative(char *path, char *cmd, int repo_to_delete, int j)
{
	int		i;
	int		char_to_delete;
	char	*path_2;
	char	*cmd_2;
	char	*exec;

	i = 0;
	char_to_delete = 0;
	while (path[i])
		i++;
	while (repo_to_delete > 0)
	{
		if (path[i] == '/')
			repo_to_delete--;
		i--;
		char_to_delete++;
	}
	char_to_delete -= 2;
	path_2 = ft_substr(path, 0, (ft_strlen(path) - char_to_delete));
	cmd_2 = ft_substr(cmd, (j * 3), (ft_strlen(cmd) - j));
	exec = ft_strjoin_path(path_2, cmd_2);
	return (free(path_2), free(cmd_2), exec);
}

void	get_command_path_3(t_sh	*sh, t_pipe	*pipe_lst)
{
	int		i;
	char	path[256];
	char	*executable;

	executable = NULL;
	i = 0;
	getcwd(path, sizeof(path));
	while (pipe_lst->cmd[i] && pipe_lst->cmd[i] == '.'
		&& pipe_lst->cmd[i + 1] == '.' && pipe_lst->cmd[i + 2] == '/')
		i += 3;
	executable = get_exec_relative(path, pipe_lst->cmd, i / 3, i / 3);
	pipe_lst->cmd_verified = ft_strdup(executable);
	free(executable);
	if (access(pipe_lst->cmd_verified, F_OK) != 0)
	{
		ft_putstr_fd("bash: ", 2);
		ft_putstr_fd(pipe_lst->cmd, 2);
		ft_putstr_fd(": No such file or directory\n", 1);
		sh->exit = 127;
	}
}
