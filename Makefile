NAME := minishell

CC := cc
CFLAG = -Wall -Wextra -Werror -I${INCLUDE_DIR} -I${LIBFT_DIR}
RM := rm
RM_FLAG := -rf
SRCS_DIR := srcs
GNL_DIR := get_next_line
GNL_FLAG := -I$(GNL_DIR)
INCLUDE_DIR := include
LIBFT_DIR := libft
LIBFT := ${LIBFT_DIR}/libft.a

KERNEL := ${shell uname}

ifeq (${KERNEL},Darwin)
	CFLAG +=  -I$(shell brew --prefix readline)/include ${shell echo > ~/.inputrc set echo-control-characters off}
	READLINE_FLAG  = -L$(shell brew --prefix readline)/lib -lreadline
else
	READLINE_FLAG  = -lreadline
endif

SRCS := ${SRCS_DIR}/main.c \
	${SRCS_DIR}/prompt.c \
	${SRCS_DIR}/tokenize.c \
	${SRCS_DIR}/tokenize2.c \
	${SRCS_DIR}/tokenize3.c \
	${SRCS_DIR}/ft_string.c \
	${SRCS_DIR}/eval.c \
	${SRCS_DIR}/eval2.c \
	${SRCS_DIR}/eval3.c \
	${SRCS_DIR}/parser.c \
	${SRCS_DIR}/parser2.c \
	${SRCS_DIR}/parser3.c \
	${SRCS_DIR}/parser4.c \
	${SRCS_DIR}/parser5.c \
	${SRCS_DIR}/expand_here_doc.c \
	${SRCS_DIR}/env.c \
	${SRCS_DIR}/env2.c \
	${SRCS_DIR}/env3.c \
	${SRCS_DIR}/ft_signal.c \
	${SRCS_DIR}/expand_env.c \
	${SRCS_DIR}/expand_env2.c \
	${SRCS_DIR}/command_exec.c \
	${SRCS_DIR}/command_exec2.c \
	${SRCS_DIR}/command_exec3.c \
	${SRCS_DIR}/command_exec4.c \
	${SRCS_DIR}/command_exec5.c \
	${SRCS_DIR}/command_exec6.c \
	${SRCS_DIR}/command_exit.c \
	${SRCS_DIR}/generate_no_exist_file_name.c \
	${GNL_DIR}/get_next_line.c \
	${SRCS_DIR}/command_cd.c \
	${SRCS_DIR}/command_echo.c \
	${SRCS_DIR}/command_export.c \
	${SRCS_DIR}/command_pwd.c \
	${SRCS_DIR}/command_unset.c \
	${SRCS_DIR}/print_lib.c \
	${SRCS_DIR}/buildin_utils.c \
	${SRCS_DIR}/ft_strcmp.c \
	${SRCS_DIR}/ft_xcalloc.c \
	${SRCS_DIR}/ft_xsplit.c \
	${SRCS_DIR}/signal_handler.c \

OBJS := ${SRCS:%.c=%.o}

all : ${NAME}

${NAME} : ${LIBFT} ${OBJS}
	${CC} ${CFLAG} ${GNL_FLAG} ${OBJS} ${LIBFT} ${READLINE_FLAG} -o ${NAME}

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

docker:
	docker compose run --rm minishell

.PHONY: all clean fclean re docker