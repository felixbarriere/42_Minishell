/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_f.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 18:02:57 by ccalas            #+#    #+#             */
/*   Updated: 2022/06/15 13:50:06 by marvin           ###   ########.fr       */
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
void	ft_init_values(t_sh *sh, char **env);

/******** INIT ********/
void	ft_init_env_values(t_env *env);

/*********** ENV ***********/
// t_env	*ft_init_env(char **env_init, t_sh *sh);
void	ft_init_env(char **env_init, t_sh *sh);
void	get_path(t_sh *sh);

/******** ENV_UTILS ********/
void	ft_free(char **str);
void	ft_free_2(char *str);
void	ft_free_3(t_env *list);

/******** PROMPT ********/
void	ft_prompt_start(t_sh *sh);
void	ft_prompt_init(t_sh *sh, char **env_init);

/******** SIGNALS ********/
void	ft_signals_orchestrator(void);

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
int		token_str(t_sh *sh);
void	tokenizer(t_sh *sh);

/******** TOKENIZER_UTILS ********/
int		len_to_dup(char *prompt);
char	*string_token(t_sh *sh, char *prompt);
char	*join_dollar_value(char *str, char *new_str,
			char *dollar_value, int idx);
char	*severals_wds_value(t_sh *sh, char *dollar_value, char	*new_str);

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

/******** GET_COMMAND_TYPE ********/
void	update_command(t_sh *sh);
void	get_commands_type(t_sh *sh);

/******** REDIRECTIONS ********/
int	update_fdout(t_pipe **pipe_lst);
int	update_fdin(t_pipe **pipe_lst);

/******** HEREDOC ********/
int		contains_any_quotes(char *str);
char	*trim_quotes(char **value, int *i, int *j);
char	*process_quotes_limiter(char **value);
int		heredoc(char *limiter, t_pipe **pipe_lst);

/******** HEREDOC_2 ********/
char	*read_heredoc(t_pipe **pipe_lst, int quotes, char *limiter);

/******** GET_COMMANDS_PATH ********/
void	get_command_path(t_sh *sh);

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
void	execution(t_pipe	*pipe_lst, char **env_init);
void	index_builtins(t_pipe	*pipe);
void	cd_command(t_pipe	*pipe);
void	pwd_command(t_pipe	*pipe);
void	echo_command(t_pipe	*pipe);

#endif