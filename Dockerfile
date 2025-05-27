FROM ubuntu:24.04

RUN apt update && apt install -y gcc make libreadline-dev tini

COPY ./srcs/            /home/workspace/minishell/srcs/
COPY ./include/         /home/workspace/minishell/include/
COPY ./libft/           /home/workspace/minishell/libft/
COPY ./get_next_line/   /home/workspace/minishell/get_next_line/
COPY ./Makefile         /home/workspace/minishell/Makefile

RUN make -C /home/workspace/minishell/ re

CMD [ "home/workspace/minishell/minishell" ]

