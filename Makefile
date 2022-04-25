NAME =		minishell

SRCS	=	main.c\
src/parser_utils.c\
src/parser.c\
src/quotes.c\
src/prompt.c\
src/lists.c\
src/signals.c\
src/env.c

OBJS = ${SRCS:.c=.o}
INCS	=	-I ./includes -I ./libft/includes
LIBC	=	libft/libft.a
CC		=	clang
CFLAGS	=	-Wall -Wextra -Werror
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

.PHONY:		all clean fclean re
