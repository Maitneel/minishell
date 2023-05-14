NAME := minishell

CC := cc
CFLAG = -Wall -Wextra -Werror  -I$(shell brew --prefix readline)/include -I${INCLUDE_DIR}
READLINE_FLAG  = -I$(shell brew --prefix readline)/include -L$(shell brew --prefix readline)/lib -lreadline
RM := rm
RM_FLAG := -rf
SRCS_DIR := srcs
INCLUDE_DIR := include

SRCS := ${SRCS_DIR}/main.c \
	${SRCS_DIR}/prompt.c \
	${SRCS_DIR}/tokenize.c \

OBJS := ${SRCS:%.c=%.o}

all : ${NAME}

${NAME} : ${OBJS}
	${CC} ${CFLAG} ${READLINE_FLAG} ${OBJS} -o ${NAME}

%.o : %.c
	${CC} ${CFLAG}  $^ -c -o $@

clean :
	${RM} ${RM_FLAG} ${OBJS}

fclean : clean
	${RM} ${RM_FLAG} ${NAME}

re : fclean all

test : ${NAME}
	./${NAME}

42readline:
	# curl -fsSL https://rawgit.com/gcamerli/42brew/master/set.sh | zsh
	exec ${SHELL} -l
	# brew install readline

.PHONY: all clean fclean re