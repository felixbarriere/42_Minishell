#ifndef MINISHELL_F_H
# define MINISHELL_F_H

#include "minishell.h"
#include "minishell_d.h"
#include "minishell_s.h"
#include "minishell_e.h"

/**************** FUNCTIONS ****************/

/****** MAIN ******/
void	ft_init_values(t_sh *sh);

/****** ENV *******/
char	**ft_init_env(void);

/****** PROMPT ******/
void	ft_prompt_start(t_sh *sh);
void	ft_prompt_init(t_sh *sh);

/****** SIGNALS ******/
void	ft_signals_orchestrator(void);

/****** PARSER UTILS ******/
int		is_in_charset(char c);
int		is_only_space(char *str);
int		ft_parse_red(t_sh *sh);

/****** QUOTES ******/
int		ft_is_quote_ok(t_sh *sh);
void	ft_find_quote_state(t_sh *sh, int i);

/****** PARSER  ******/
void	process_redirect_token(t_sh *sh);
char 	*string_token(t_sh *sh, char *prompt);
void	tokenizer(t_sh *sh);
void 	lexer(t_sh *sh);

/****** LISTS  ******/
void	ft_set_null_free_elem(t_token *elem);
void	ft_set_null_free_list(t_token **a_list);
t_token *create_token(t_token_type type, char *value);
t_token *add_back_token(t_token *list, t_token_type type, char *value);
void	print_tokens(t_token *li);
int		list_length(t_token *li);

#endif