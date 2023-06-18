NAME := microshell-00

CC := cc
CFLAG := -g -Wall -Wextra -Werror
RM := rm
RM_FLAG := -rf

SRCS := main.c \
		prompt.c \
		get_next_line.c \
		utils.c \
		export.c \
		pwd.c \
		cd.c \
		unset.c \
		echo.c \
		print_lib.c \
		strerror.c \
		env.c \
		env2.c \
		ft_split.c \
		ft_strcmp.c \

LIBFT_DIR = ../libft
LIBFT = ${LIBFT_DIR}/libft.a
LIBFT_FLAG = -L${LIBFT_DIR} -lft

OBJS := ${SRCS:%.c=%.o}

all : ${NAME}

${NAME} :  ${LIBFT_DIR}/libft.a ${OBJS}
	${CC} ${CFLAG} ${OBJS} -o ${NAME} ${LIBFT_FLAG}

${LIBFT_DIR}/libft.a: ${LIBFT_DIR}/*.c
	make -C ${LIBFT_DIR}

%.o : %.c
	${CC} ${CFLAG} -I ${LIBFT_DIR} $^ -c -o $@

debug:
	$(CC) -g *.c -o $(NAME)

clean :
	${RM} ${RM_FLAG} ${OBJS}

fclean : clean
	${RM} ${RM_FLAG} ${NAME}

re : fclean all

test : ${NAME}
	./${NAME}

.PHONY: all clean fclean re debug