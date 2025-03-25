CC := cc

CFLAGS := -Wall -Wextra -Werror
# CFLAGS := -Wall -Wextra -Werror -fsanitize=address -g
# CFLAGS := -Wall -Wextra -Werror -w
# CFLAGS := -fsanitize=address -Werror

RM := rm -f

NAME := pipex

MANDO := mandatory

BNS := bonus

UTILS := mandatory/utils

UTILS_BNS := bonus/utils

GNL_BNS := bonus/gnl

SRC := ${MANDO}/pipex.c ${MANDO}/pipex_utils.c ${MANDO}/error_handlers.c ${MANDO}/child_process.c \
		${UTILS}/ft_putstr.c ${UTILS}/ft_strlen.c ${UTILS}/ft_split.c ${UTILS}/ft_strstr.c \
		${UTILS}/ft_strdup.c ${UTILS}/ft_strjoin.c ${UTILS}/ft_strrchr.c

SRC_BNS := ${BNS}/pipex_bonus.c ${BNS}/pipex_utils_bonus.c ${BNS}/error_handlers_bonus.c ${BNS}/child_process_bonus.c \
		${UTILS_BNS}/ft_putstr_bonus.c ${UTILS_BNS}/ft_split_bonus.c ${UTILS_BNS}/ft_strstr_bonus.c \
		${UTILS_BNS}/ft_strjoin_bonus.c ${UTILS_BNS}/ft_strrchr_bonus.c \
		${GNL_BNS}/get_next_line_bonus.c ${GNL_BNS}/get_next_line_utils_bonus.c

OBJS := ${SRC:.c=.o}

OBJS_BNS := ${SRC_BNS:.c=.o}

all: ${NAME}

${NAME}: ${OBJS} ${MANDO}/pipex.h
	${CC} ${CFLAGS} ${OBJS} -o ${NAME}
	@${RM} ${OBJS_BNS}

bonus: .bonus

.bonus: ${OBJS_BNS} ${BNS}/pipex_bonus.h ${GNL_BNS}/get_next_line_bonus.h
	${CC} ${CFLAGS} ${OBJS_BNS} -o ${NAME}
	@touch .bonus
	@${RM} ${OBJS}

%.o: %.c
	${CC} ${CFLAGS} -c $< -o $@

bonus/%.o: bonus/%.c
	${CC} ${CFLAGS} -c $< -o $@

clean:
	@${RM} ${OBJS} ${OBJS_BNS} .bonus

fclean: clean
	@${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re