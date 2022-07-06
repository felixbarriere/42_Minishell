/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccalas <ccalas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 17:43:57 by fbarrier          #+#    #+#             */
/*   Updated: 2022/07/06 12:27:55 by ccalas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/minishell_d.h"
#include "../include/minishell_f.h"
#include "../include/minishell_s.h"

void	dup_env_array(t_sh *sh, char **env)
{
	int	i;

	i = 0;
	while (env[i] != NULL)
		i++;
	sh->env = malloc (sizeof(char *) * (i + 1));
	if (!sh->env)
		return ;
	i = 0;
	while (env[i] != NULL)
	{
		sh->env[i] = ft_strdup(env[i]);
		i++;
	}
	sh->env[i] = NULL;
}

void	ft_prompt_start(t_sh *sh)
{
	sh->prompt = readline("➜ minishell ");
	if (!sh->prompt)
	{
		if (sh->path != NULL)
			ft_free(sh->path);
		ft_free(sh->env);
		clear_list(sh->token_lst);
		clear_list_pipe(sh->pipe_lst);
		exit(0);
	}
	add_history(sh->prompt);
}

void	ft_prompt_init(t_sh *sh, char **env_init)
{
	dup_env_array(sh, env_init);
	ft_init_values(sh, env_init);
	sh->exit = 0;
	ft_init_env(sh->env, sh);
	get_path(sh);
	while (1)
	{
		ft_prompt_start(sh);
		sh->lenght = ft_strlen(sh->prompt);
		if (!is_only_space(sh->prompt))
			lexer(sh);
		if (sh->error)
		{
			clear_list(sh->token_lst);
			clear_list_pipe(sh->pipe_lst);
			ft_init_values(sh, env_init);
			continue ;
		}
		if (!ft_strcmp(sh->pipe_lst->cmd, "echo"))
			sh->exit = 0;
		execution(sh, sh->env);
		clear_list(sh->token_lst);
		clear_list_pipe(sh->pipe_lst);
		ft_init_values(sh, sh->env);
	}
}


// int	executor(t_pipe *cmdl, char **env)
// {
// 	if (ft_strncmp(cmdl->cmd, "echo", ft_strlen("echo") + 1) == 0)
// 		return (builtin_echo(args_to_ac(cmdl->args), cmdl->args, cmdl->fdout));
// 	else if (ft_strncmp(cmdl->cmd, "cd", ft_strlen("cd") + 1) == 0)
// 		return (builtin_cd(args_to_ac(cmdl->args), cmdl->args, penv));
// 	else if (ft_strncmp(cmdl->cmd, "pwd", ft_strlen("pwd") + 1) == 0)
// 		return (builtin_pwd(args_to_ac(cmdl->args), cmdl->fdout));
// 	else if (ft_strncmp(cmdl->cmd, "export", ft_strlen("export") + 1) == 0)
// 		return (builtin_export(args_to_ac(cmdl->args), cmdl->args, penv));
// 	else if (ft_strncmp(cmdl->cmd, "unset", ft_strlen("unset") + 1) == 0)
// 		return (builtin_unset(args_to_ac(cmdl->args), cmdl->args, penv));
// 	else if (ft_strncmp(cmdl->cmd, "env", ft_strlen("env") + 1) == 0)
// 		return (builtin_env(args_to_ac(cmdl->args), env, cmdl->fdout));
// 	else if (ft_strncmp(cmdl->cmd, "exit", ft_strlen("exit") + 1) == 0)
// 		exit((long long)cmdl->args[1]);
// 	else
// 		return (exec_bin(cmdl, env));
// }

// int	spawn_process(int fdin, int *fd, t_pipe *cmdl, t_sh *sh)
// {
// 	int	pid;
// 	int	fdout;

// 	fdout = cmdl->fdout;
// 	if (fd != NULL)
// 	{
// 		close(fd[0]);
// 		fdout = fd[1];
// 	}
// 	if (fdin != STDIN_FILENO)
// 	{
// 		dup2(fdin, STDIN_FILENO);
// 		close(fdin);
// 	}
// 	if ((fdout != STDOUT_FILENO) && (cmdl->next != NULL))
// 	{
// 		dup2(fdout, STDOUT_FILENO);
// 		close(fdout);
// 	}
// 	pid = executor(cmdl, &sh->env);

// 	// close_fds(fdin, fdout);
// 	return (pid);
// }

// void	close_fds(int fdin, int fdout)
// {
// 	if (fdin != STDIN_FILENO)
// 		close(fdin);
// 	if (fdout != STDOUT_FILENO)
// 		close(fdout);
// }

// void	set_error_exit_status(t_sh *sh, int status)
// {
// 	sh->exit = status;
// 	sh->error = 1;
// }








// void	execute_pipes(t_sh *sh)
// {
// 	int 		status;
// 	int 		fdin;
// 	int			fd[2];
// 	t_pipe	*cmdl;

// 	cmdl = sh->pipe_lst;
// 	fdin = cmdl->fdin;
// 	while (cmdl->next)
// 	{
// 		pipe(fd);
// 		cmdl->pid = spawn_process(fdin, fd, cmdl, sh);
// 		close(fd[1]);
// 		fdin = fd[0];
// 		cmdl = cmdl->next;
// 	}
// 	cmdl->pid = spawn_process(fdin, NULL, cmdl, sh);
// 	if ((sh->pipe_lst)->next != NULL)
// 		close_fds(fd[0], fd[1]);
// 	cmdl = sh->pipe_lst;
// 	while (cmdl)
// 	{
// 		if (cmdl->pid != -1)
// 			if ((0 < waitpid(cmdl->pid, &status, 0)) && (WIFEXITED(status)))
// 				set_error_exit_status(sh, WEXITSTATUS(status));
// 		cmdl = cmdl->next;
// 	}
// }



