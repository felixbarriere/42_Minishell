/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   index.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 16:12:40 by fbarrier          #+#    #+#             */
/*   Updated: 2022/06/15 13:57:51 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/minishell_d.h"
#include "../../include/minishell_f.h"
#include "../../include/minishell_s.h"

void	index_builtins(t_pipe	*pipe)
{
	if (!ft_strcmp(pipe->cmd, "cd"))
		cd_command(pipe);
	else if (!ft_strcmp(pipe->cmd, "pwd"))
		pwd_command(pipe);
	else if (!ft_strcmp(pipe->cmd, "echo"))
		echo_command(pipe);
}