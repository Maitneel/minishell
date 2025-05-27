FROM ubuntu:24.04

RUN apt update && apt install -y gcc make libreadline-dev

# RUN git clone git@github.com:ndmxjp/minishell.git /home/workspace/minishell

COPY ./resource/srcs/            /home/workspace/minishell/srcs/
COPY ./resource/include/         /home/workspace/minishell/include/
COPY ./resource/libft/           /home/workspace/minishell/libft/
COPY ./resource/get_next_line/   /home/workspace/minishell/get_next_line/
COPY ./resource/Makefile         /home/workspace/minishell/Makefile

RUN make -C /home/workspace/minishell/

CMD [ "/home/workspace/minishell" ]
