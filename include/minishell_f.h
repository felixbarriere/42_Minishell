/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_f.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccalas <ccalas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 12:02:46 by ccalas            #+#    #+#             */
/*   Updated: 2022/08/01 16:52:39 by ccalas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_F_H
# define MINISHELL_F_H

# include "minishell.h"
# include "minishell_d.h"
# include "minishell_s.h"
# include "minishell_e.h"

/**************** FUNCTIONS ****************/
/******** MAIN ********/
void	last_cmd(t_sh *sh);
void	ft_init_values(t_sh *sh, char **env);

/******** INIT ********/
void	ft_init_env_values(t_env *env);

/*********** ENV ***********/
// t_env	*ft_init_env(char **env_init, t_sh *sh);
void	ft_init_env(char **env_init, t_sh *sh);
void	get_path(t_sh *sh);
void	orchestrate_env_token(char *env_init, t_sh *sh, int index);

/******** ENV_UTILS ********/
void	ft_free(char **str);
void	ft_free_2(char *str);
void	ft_free_3(t_env *list);
char	*ft_strjoin_char_2(char *s1, char c);

/******** PROMPT ********/
void	ft_prompt_start(t_sh *sh);
void	ft_prompt_init(t_sh *sh, char **env_init);
void	ft_close_final(void);

/******** SIGNALS ********/
void	ft_signals_orchestrator(int sigquit_active);
void	heredoc_handler(int signal);

/******** LEXER ********/
void	lexer(t_sh *sh);

/******** LEXER UTILS ********/
int		contains_quotes(char *str);
int		is_in_charset(char c);
int		is_only_space(char *str);
char	*ft_strjoin_char(char *s1, char c);
char	*ft_strjoin_char_takeout(char *s1, char c, char take_out);
int		ft_parse_red(t_sh *sh); // DANS LA MAUVAISE SECTION

/******** LEXER_DOLLAR_IN_QUOTES ********/
char	*get_key_dollar_2(char *str, int i, int j);
char	*get_key_dollar(char *str, int i);
char	*get_value_dollar(t_sh	*sh, char *key);

/******** TOKENIZER ********/
void	process_redirect_token(t_sh *sh);
void	token_str(t_sh *sh);
void	tokenizer(t_sh *sh);

/******** TOKENIZER_UTILS ********/
int		len_to_dup(char *prompt);
char	*string_token(t_sh *sh, char *prompt);
char	*join_dollar_value(char *str, char *new_str,
			char *dollar_value, int idx);
char	*severals_wds_value(t_sh *sh, char *dollar_value, char	*new_str);
int		ft_strlen2(const char *s);

/******** TOKENIZER_UTILS_QUOTES ********/
char	*squote_manager(char *str, int *idx);
char	*dquote_dollar_manager(char *str, int *idx, t_sh *sh);
char	*dquote_manager(char *str, int *idx, t_sh *sh);
char	*quotes_manager(char *str, int *idx, t_sh *sh);
char	*noquote_dollar_manager(char *str, int *idx, t_sh *sh);

/******** QUOTES ********/
int		ft_is_quote_ok(t_sh *sh);
void	ft_find_quote_state(t_sh *sh, int i);

/******** PARSER ********/
void	process_redirect_token(t_sh *sh);
char	*string_token(t_sh *sh, char *prompt);
void	tokenizer(t_sh *sh);
void	lexer(t_sh *sh);
char	*expander(t_sh *sh, char *dollar);

/******** FILE REDIRECTIONS ********/
/******** GET_COMMAND_TYPE ********/
void	update_command(t_sh *sh);

/******** GET_COMMAND_TYPE_UTILS ********/
int		args_number(t_token *li);
void	find_type_args(t_token *lst, t_sh *sh);
void	find_type(t_token *lst, t_sh *sh);
void	get_commands_type(t_sh *sh);

/******** REDIRECTIONS ********/
int		open_fdin(char	*value, t_pipe **pipe_lst);
int		update_fdout(t_pipe **pipe_lst);
int		update_fdin(t_pipe **pipe_lst);
int		update_fdin_error(t_token *temp, t_pipe *pipe_lst);

/******** PROCESS_LIMITER ********/
char	*process_quotes_limiter(char **value);
int		limiter_has_quotes(char *str);
void	process_limiter(char **limiter, int *quotes);
int		is_limiter(char **temp, char **limiter);

/******** HEREDOC ********/
int		contains_any_quotes(char *str);
char	*trim_quotes(char **value, int *i, int *j);
char	*process_quotes_limiter(char **value);
int		heredoc(char *limiter, t_pipe **pipe_lst);

/******** HEREDOC_2 ********/
char	*read_heredoc(t_pipe **pipe_lst, int quotes, char *limiter);
int		init_heredoc(t_pipe **pipe_lst);
int		heredoc2(char *limiter, t_pipe **pipe_lst, int quotes);
void	free_free_all(t_sh *sh);
int		wait_heredoc(pid_t pid, int *status, t_pipe *pipe_lst);
/******** HEREDOC_UTILS ********/
int		contains_charset(char *str, char c);
int		contain_space(char	**value);

/******** FILE PIPES ********/
/******** GET_COMMANDS_PATH ********/
void	get_command_path(t_sh *sh);
char	*ft_strjoin_path(char *s1, char *s2);
char	*ft_strjoin_path_2(char *dest, char *s1, char *s2);
void	get_command_path_3(t_sh	*sh, t_pipe	*pipe_lst);

/******** PIPE_CREATION ********/
void	pipe_creation(t_sh *sh);
void	print_pipe_tokens(t_pipe *li);

/******** ERROR_SEP ********/
bool	is_type(t_token *current, t_token_type type);
int		check_error_sep(t_token *token_lst);
int		check_error_sep_0(t_token *token_lst);
int		check_error_sep_1(t_token *token_lst);
int		check_error_sep_2(t_token *token_lst);
int		check_error_sep_3(t_token *token_lst);

/******** ERROR_SEP2 ********/
int		check_error_sep_4(t_token *token_lst);
int		check_error_sep_5(t_token *token_lst);
int		check_error_sep_6(t_token *token_lst);

/******** LISTS  ********/
int		ft_lstlast_dr_left(t_token *lst);
void	ft_set_null_free_elem(t_env *elem);
t_token	*create_token(t_token_type type, char *value);
t_token	*add_back_token(t_token *list, t_token_type type, char *value);
void	print_tokens(t_token *li);
int		list_length(t_token *li);
void	clear_list(t_token *a_li);
t_token	*pop_front_list(t_token *li);
bool	is_empty_list(t_token *li);
void	clear_list_env(t_env *a_li);
t_env	*pop_front_list_env(t_env *li);
void	ft_set_null_free_elem_2(t_token *elem);
void	ft_set_null_free_elem_pipe(t_pipe *elem);
void	clear_list_pipe(t_pipe *a_list);

/******** EXECUTION ********/
void	index_builtins(t_sh	*sh, t_pipe *start);
void	cd_command(t_sh	*sh, t_pipe *pipe_lst);
void	error_cd(char	*bad_dir);
void	cd_home(t_sh *sh, char *old_path);
void	change_all_pwd(t_sh *sh, char *old_path);
void	change_pwd(t_sh	*sh, char *path);
void	change_old_pwd(t_sh	*sh, char *old_path);
void	pwd_command(t_sh *sh, t_pipe	*pipe);
void	echo_command(t_sh *sh, t_pipe *pipe_lst);
int		only_n(char	*str);
void	env_command(t_sh *sh, t_pipe *pipe_lst);
void	export_command(t_sh *sh, t_pipe *start);
void	update_value_null(t_env	*list, char *key);
int		is_in_env(char	*key, t_env	*list);
int		contains_equal(char *str, t_sh *sh);
char	*delete_plus(char *src);
void	global_get_value(char **key_value, t_sh *sh, char *value,
			char *for_val);
void	update_value(t_env	*list, char	*value, char *key);
char	*get_value(char **key_value);
char	*get_former_value(char *key, t_env *list);
void	unset_command(t_sh *sh, t_pipe *pipe_lst);
void	exit_command(t_sh *sh, t_pipe *pipe_lst);
int		check_max(char *str);
int		is_in_range(char *str);
int		check_min(char *str);
int		ft_strlen_3(const char *s);

/******** EXECUTION ********/
void	execution(t_sh *sh, char **env_init, int nb_pipes, t_pipe	*start);
int		nb_pipe(t_pipe *pipe_lst);
void	init_pipe(t_pipe *start, int nb_pipes);

/******** EXECUTION_IN_OUPUT ********/
void	update_input_output(t_pipe *pipe_lst);
void	reset_input_output(t_pipe *pipe_lst);

/******** EXECUTION_UTILS ********/
void	ft_close(t_sh *sh, int nb_pipes);
void	ft_switch(t_pipe *start, int k);
void	mess_cmd_not_found(t_sh *sh, char *cmd);
char	*ft_strjoin_path_2(char *dest, char *s1, char *s2);
char	*ft_strjoin_path(char *s1, char *s2);

/******** EXECUTION_NO_PIPE ********/
void	no_pipe_exec(t_sh *sh, char **env_init);
void	wait_get_status_no_pipe(t_sh *sh);

/******** EXECUTION_PIPE ********/
void	execution_pipe(t_sh *sh, t_pipe *start, int nb_pipes, char **env_init);

/******** EXECUTION_WAIT_STATUS ********/
void	wait_get_status(t_sh *sh, int nb_pipes);

void	update_path(t_sh *sh, char *key);
void	env_command_export(t_sh	*sh);
void	wait_get_status(t_sh *sh, int nb_pipes);
void	control_sigquit(t_sh *sh);
/******** PIPEX ********/
void	ft_close2(void);
void	free_free_all(t_sh *sh);

#endif