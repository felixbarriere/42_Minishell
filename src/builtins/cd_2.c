/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarrier <fbarrier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 16:47:49 by fbarrier          #+#    #+#             */
/*   Updated: 2022/06/26 16:49:59 by fbarrier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/minishell_d.h"
#include "../../include/minishell_f.h"
#include "../../include/minishell_s.h"

void	error_cd(char	*bad_dir)
{
	ft_putstr_fd("cd: no such file or directory: ", 2);
	ft_putstr_fd(bad_dir, 2);
	ft_putchar_fd('\n', 2);
}
