NAME = minishell

SRCS	=	main.c\
			
OBJS	=	${SRCS:.c=.o}
CC		=	gcc
FLAGS	=	-Wall -Wextra -Werror -lreadline

INCS = -I ./includes -I ./libft/includes
LIBC = -L ./libft -lft
HEADER_MESSAGE = MINISHELL${_END}

all:		${NAME}

.c.o:
			@${CC} ${FLAGS} ${INCS} -c $< -o $@

${NAME}:	${OBJS}
			@echo "[${HEADER_MESSAGE}]"
			@echo "[1 / 2] Compiling libft..."
			@${MAKE} -C libft >/dev/null
			@echo "[2 / 2] Compiling Minishell..."
			@${CC} ${FLAGS} ${INCS} ${LIBC} -o ${NAME} ${OBJS}
			@echo "Minishell ready to be used !"

clean:		
			@echo "Deleting libft library..."
			@${MAKE} -C libft clean >/dev/null
			@echo "Deleting minishell binary files..."
			@rm -f ${OBJS}

fclean:		clean
			@${MAKE} -C libft fclean >/dev/null
			@echo "Deleting minishell executable..."
			@rm -f ${NAME}
			@echo "Minishell's has been cleaned !"

re:			fclean all

.PHONY:		all fclean clean all bonus