/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_f.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccalas <ccalas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 18:02:57 by ccalas            #+#    #+#             */
/*   Updated: 2022/05/06 12:13:20 by ccalas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_F_H
# define MINISHELL_F_H

#include "minishell.h"
#include "minishell_d.h"
#include "minishell_s.h"
#include "minishell_e.h"

/**************** FUNCTIONS ****************/

/******** MAIN ********/
void	ft_init_values(t_sh *sh, char **env);

/******** INIT ********/
void	ft_init_env_values(t_env *env);

/******** ENV ********/
// t_env	*ft_init_env(char **env_init, t_sh *sh);
void	ft_init_env(char **env_init, t_sh *sh);

/******** PROMPT ********/
void	ft_prompt_start(t_sh *sh);
void	ft_prompt_init(t_sh *sh, char **env_init);

/******** SIGNALS ********/
void	ft_signals_orchestrator(void);

/******** PARSER UTILS ********/
int		is_in_charset(char c);
int		is_only_space(char *str);
int		ft_parse_red(t_sh *sh);

/******** QUOTES ********/
int		ft_is_quote_ok(t_sh *sh);
void	ft_find_quote_state(t_sh *sh, int i);

/******** PARSER ********/
void	process_redirect_token(t_sh *sh);
char 	*string_token(t_sh *sh, char *prompt);
void	tokenizer(t_sh *sh);
void 	lexer(t_sh *sh);

/******** ERROR_SEP ********/
bool	is_type(t_token* current, t_token_type type);
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
void	ft_set_null_free_elem(t_token *elem);
void	ft_set_null_free_list(t_token **a_list);
t_token *create_token(t_token_type type, char *value);
t_token *add_back_token(t_token *list, t_token_type type, char *value);
void	print_tokens(t_token *li);
int		list_length(t_token *li);
void	clear_list(t_token *li);
t_token *pop_front_list(t_token *li);
bool 	is_empty_list(t_token *li);

#endif