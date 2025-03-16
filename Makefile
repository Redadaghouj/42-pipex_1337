CC := cc

#CFLAGS := -Wall -Wextra -Werror
CFLAGS := -fsanitize=address -Werror

RM := rm -f

NAME := pipex

MANDO := mandatory

SRC := ${MANDO}/pipex.c

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