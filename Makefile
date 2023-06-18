NAME := minishell

CC := cc
CFLAG = -Wall -Wextra -Werror  -I$(shell brew --prefix readline)/include -I${INCLUDE_DIR} -I${LIBFT_DIR}
READLINE_FLAG  = -I$(shell brew --prefix readline)/include -L$(shell brew --prefix readline)/lib -lreadline
RM := rm
RM_FLAG := -rf
SRCS_DIR := srcs
GNL_DIR := get_next_line
GNL_FLAG := -I$(GNL_DIR)
INCLUDE_DIR := include
LIBFT_DIR := libft
LIBFT := ${LIBFT_DIR}/libft.a

SRCS := ${SRCS_DIR}/main.c \
	${SRCS_DIR}/prompt.c \
	${SRCS_DIR}/tokenize.c \
	${SRCS_DIR}/ft_string.c \
	${SRCS_DIR}/eval.c \
	${SRCS_DIR}/parser.c \
	${SRCS_DIR}/env.c \
	${SRCS_DIR}/env2.c \
	${SRCS_DIR}/ft_signal.c \
	${SRCS_DIR}/expand_env.c \
	${SRCS_DIR}/command_exec.c \
	${GNL_DIR}/get_next_line.c \
	${SRCS_DIR}/command_cd.c \
	${SRCS_DIR}/command_echo.c \
	${SRCS_DIR}/command_export.c \
	${SRCS_DIR}/command_pwd.c \
	${SRCS_DIR}/command_unset.c \
	${SRCS_DIR}/buildin_print_lib.c \
	${SRCS_DIR}/buildin_utils.c \
	${SRCS_DIR}/ft_strcmp.c \

OBJS := ${SRCS:%.c=%.o}

all : ${NAME}

${NAME} : ${LIBFT} ${OBJS}
	${CC} ${CFLAG} ${READLINE_FLAG} ${GNL_FLAG} ${OBJS} ${LIBFT} -o ${NAME}

${LIBFT} : ${LIBFT_DIR}/*.c
	make -C ${LIBFT_DIR}

%.o : %.c
	${CC} ${CFLAG} ${GNL_FLAG} $^ -c -o $@

clean :
	make -C ${LIBFT_DIR} fclean
	${RM} ${RM_FLAG} ${OBJS}

fclean : clean
	${RM} ${RM_FLAG} ${NAME}

re : fclean all

soft_clean : 
	${RM} ${RM_FLAG} ${OBJS}

sre : soft_clean all

test : ${NAME}
	./${NAME}

42readline:
	# curl -fsSL https://rawgit.com/gcamerli/42brew/master/set.sh | zsh
	exec ${SHELL} -l
	# brew install readline

.PHONY: all clean fclean re