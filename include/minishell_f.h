#ifndef MINISHELL_F_H
# define MINISHELL_F_H

#include "minishell.h"
#include "minishell_d.h"
#include "minishell_s.h"

/**************** FUNCTIONS ****************/

/****** MAIN ******/
void	ft_init_values(t_sh *sh);

/****** PROMPT ******/
void	ft_prompt_start(t_sh *sh);
void	ft_prompt_init(t_sh *sh);


/****** PARSER UTILS ******/
int	isin_charset(char c);
int	isonly_space(char *str);
int	ft_parse_red(t_sh *sh);

/****** PARSER  ******/
char 	*string_token(t_sh *sh, char *prompt);
void	tokenizer(t_sh *sh, char first, char second);
void 	lexer(t_sh *sh);

/****** LISTS  ******/
t_token *create_token(t_token_type type, char *value);
t_token *add_back_token(t_token *list, t_token_type type, char *value);
void	print_tokens(t_token *li);
int		list_length(t_token *li);

#endif