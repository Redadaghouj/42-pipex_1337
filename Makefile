CC := cc

#CFLAGS := -Wall -Wextra -Werror
CFLAGS := -fsanitize=address -Werror

RM := rm -f

NAME := pipex

MANDO := mandatory

UTILS := mandatory/utils

SRC := ${MANDO}/pipex.c ${MANDO}/pipex_utils.c ${MANDO}/error_handlers.c \
		${UTILS}/ft_putstr.c ${UTILS}/ft_strlen.c ${UTILS}/ft_split.c

OBJS := ${SRC:.c=.o}

all: ${NAME}

#################-REMOVE-################################

dev: ${NAME} clean
	clear

#################-REMOVE-################################

${NAME}: ${OBJS} ${MANDO}/pipex.h
	${CC} ${CFLAGS} ${OBJS} -o ${NAME}

%.o: %.c
	${CC} ${CFLAGS} -c $< -o $@

clean:
	@${RM} ${OBJS}

fclean: clean
	@${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re