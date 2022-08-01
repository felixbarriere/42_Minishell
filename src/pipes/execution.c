/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccalas <ccalas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 14:59:40 by fbarrier          #+#    #+#             */
/*   Updated: 2022/08/01 16:54:03 by ccalas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/minishell_d.h"
#include "../../include/minishell_f.h"
#include "../../include/minishell_s.h"

extern t_sh	g_sh;

void	init_pipe(t_pipe *start, int nb_pipes)
{
	int	i;

	i = 0;
	while (i < nb_pipes)
	{
		if (pipe(start->fd) == -1)
			return ;
		start = start->next;
		i++;
	}
}

int	nb_pipe(t_pipe *pipe_lst)
{
	int		nb_pipes;
	t_pipe	*start;

	start = pipe_lst;
	nb_pipes = 0;
	while (start->next)
	{
		nb_pipes++;
		start = start->next;
	}
	return (nb_pipes);
}

void	ft_sh_exit(void)
{
	if (g_sh.exit == 13)
		g_sh.exit = 127;
}

void	execution(t_sh *sh, char **env_init, int nb_pipes, t_pipe *start)
{
	start = sh->pipe_lst;
	sh->exec_pipe_k = 0;
	nb_pipes = nb_pipe(sh->pipe_lst);
	if (nb_pipes == 0)
	{
		if (start->pipe_ok != 1)
		{
			if (sh->pipe_lst->is_builtin != 1 && start->cmd
				&& sh->pipe_lst->cmd_verified == NULL)
			{
				mess_cmd_not_found(sh, sh->pipe_lst->cmd);
				return ;
			}
			update_input_output(sh->pipe_lst);
			if (sh->pipe_lst->is_builtin == 1)
				index_builtins(sh, start);
			else if (sh->pipe_lst->cmd_verified != NULL)
				no_pipe_exec(sh, env_init);
			reset_input_output(sh->pipe_lst);
		}
	}
	else
		execution_pipe(sh, start, nb_pipes, env_init);
	ft_sh_exit();
}

/*
void	execution_pipe(t_sh *sh, t_pipe *start, int nb_pipes, char **env_init)
{
	sh->exec_pipe_i = 0;
	sh->exec_pipe_k = 0;
	init_pipe(start, nb_pipes);
	while (start)
	{
		update_input_output(start);
		ft_switch(start, sh->exec_pipe_k);
		if (!ft_strcmp(start->token->value, "<<"))
		{
			start = start->next;
			reset_input_output(sh->pipe_lst);
			continue ;
		}
		if (start->is_builtin != 1 && start->cmd_verified == NULL)
		{
			mess_cmd_not_found(sh, start->cmd);
			reset_input_output(sh->pipe_lst);
			return ;
		}
		execution_pipe2(sh, start, nb_pipes, env_init);
		execution_pipe3(sh);
		start = start->next;
	}
	ft_close(sh, nb_pipes);
	wait_get_status(sh, nb_pipes, sh->exec_pid);
}
*/