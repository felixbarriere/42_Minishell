/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_s.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccalas <ccalas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 18:02:57 by ccalas            #+#    #+#             */
/*   Updated: 2022/07/31 17:16:27 by ccalas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_S_H
# define MINISHELL_S_H

# include "minishell.h"
# include "minishell_d.h"
# include "minishell_f.h"
# include "minishell_e.h"

/**************** STRUCTURES ****************/
/* liste chaînée. Chaque token représente un caractère tokenisé, 
chaîné au token précédent / suivant
 */
typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*prev;
	struct s_token	*next;
}	t_token;

/* liste chainee representant les variables d'environnement */
typedef struct s_env
{
	t_token_type	type;
	char			*full;
	char			*key;
	char			*value;
	int				index;
	struct s_env	*prev;
	struct s_env	*next;
}	t_env;

/* liste chainee representant les commandes autours des pipes */
typedef struct s_pipe
{
	pid_t			pid;
	t_token			*token;
	int				pipe_ok;
	int				cmd_ok;
	int				fd[2];
	int				cpy_input;
	int				cpy_output;
	char			*cmd;
	char			*cmd_verified;
	char			**args;
	int				input;
	int				output;
	int				append_mode;
	int				heredoc_mode;
	char			*limiter_name;
	int				infile;
	int				outfile;
	int				is_builtin;
	struct s_pipe	*prev;
	struct s_pipe	*next;
}	t_pipe;

/* structure principale du programe */
typedef struct s_sh
{
	int		exec_pipe_k;
	int		exec_nb_cmds_valids;
	char	**env;
	pid_t	pid1;
	pid_t	pid2;
	char	**path;
	t_env	*env_lst;
	t_pipe	*pipe_lst;
	int		e_index;
	t_token	*token_lst;
	char	*prompt;
	int		p_index;
	int		lenght;
	int		error;
	int		exit;
	int		state_quote;
	int		ts_idx;
	int		ts_i;
	pid_t	exec_pid;
	char	*limiter;
}	t_sh;

#endif