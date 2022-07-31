
NAME =		minishell

SRCS	=	main.c\
src/lexer/lexer_utils.c\
src/lexer/lexer_dollar.c\
src/lexer/tokenizer.c\
src/lexer/tokenizer_utils_quotes.c\
src/lexer/tokenizer_utils.c\
src/lexer/lexer.c\
src/lexer/quotes.c\
src/prompt.c\
src/lists/lists.c\
src/lists/lists_2.c\
src/lists/lists_3.c\
src/pipes/pipe_creation.c\
src/pipes/get_command_path.c\
src/pipes/get_command_path_2.c\
src/pipes/execution.c\
src/pipes/execution_no_pipe.c\
src/pipes/execution_pipes.c\
src/pipes/execution_utils.c\
src/pipes/execution_in_output.c\
src/pipes/execution_wait_status.c\
src/redirections/get_command_type.c\
src/redirections/get_command_type_utils.c\
src/redirections/redirections.c\
src/redirections/process_limiter.c\
src/redirections/heredoc.c\
src/redirections/heredoc_utils.c\
src/redirections/heredoc2.c\
src/redirections/heredoc3.c\
src/signals.c\
src/env/env.c\
src/env/env_utils.c\
src/init.c\
src/error_sep/error_sep.c\
src/error_sep/error_sep2.c\
src/parser/expander.c\
src/builtins/index.c\
src/builtins/cd.c\
src/builtins/cd_2.c\
src/builtins/pwd.c\
src/builtins/echo.c\
src/builtins/echo_2.c\
src/builtins/env_cmd.c\
src/builtins/export.c\
src/builtins/export_2.c\
src/builtins/export_3.c\
src/builtins/unset.c\
src/builtins/exit.c\
src/builtins/exit_2.c\

OBJS = ${SRCS:.c=.o}
INCS	=	-I ./includes -I ./libft/includes
LIBC	=	libft/libft.a
CC		=	clang
CFLAGS	=	-Wall -Wextra -Werror #-fsanitize=address -g3
RM		=	rm -rf
SYSTEM	=	${shell uname}


.c.o:
			${CC} ${CFLAGS} ${INCS} -c $< -o $@

all:		${NAME}

${NAME}:	${OBJS}
			@${MAKE} -C libft > /dev/null
			${CC} ${CFLAGS} -lreadline ${INCS} ${OBJS} -o ${NAME} ${LIBC}

clean:
			@${MAKE} -C libft clean > /dev/null
			${RM} ${OBJS}

fclean:		clean
			@${MAKE} -C libft fclean > /dev/null
			${RM} ${NAME}

re:			fclean all

valgrind: ${NAME}
	@valgrind --suppressions=cmd_valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes --track-origins=yes --verbose --log-file=valgrind-out.txt ./minishell
	#@vim valgrind-out.txt

.PHONY:		all clean fclean re
