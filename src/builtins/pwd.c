/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarrier <fbarrier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 17:14:24 by fbarrier          #+#    #+#             */
/*   Updated: 2022/06/26 17:09:09 by fbarrier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/minishell_d.h"
#include "../../include/minishell_f.h"
#include "../../include/minishell_s.h"

void	pwd_command(t_pipe	*pipe)
{
	char	cwd[256];

	(void)pipe;
	if (getcwd(cwd, sizeof(cwd)) == NULL)
		write (2, "error pwd\n", 10);
	else
	{
		ft_putstr_fd(cwd, 1);
		ft_putchar_fd('\n', 1);
	}
}
