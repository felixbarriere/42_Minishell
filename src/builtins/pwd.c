/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 17:14:24 by fbarrier          #+#    #+#             */
/*   Updated: 2022/06/15 13:05:09 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/minishell_d.h"
#include "../../include/minishell_f.h"
#include "../../include/minishell_s.h"

void	pwd_command(t_pipe	*pipe)
{
	(void)pipe;
	char cwd[256];
	
	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		write (2, "error pwd\n", 10);
	}
	else {
		ft_putstr_fd(cwd, 1);
		ft_putchar_fd('\n', 1);
	}


	
}