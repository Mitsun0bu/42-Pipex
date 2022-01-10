# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: llethuil <llethuil@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/09 11:45:29 by llethuil          #+#    #+#              #
#    Updated: 2022/01/10 20:05:17 by llethuil         ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #



NAME = pipex

INCS = 		./includes/pipex.h \

SRCS =		./srcs/main.c			\
			./srcs/utils_1.c		\
			./srcs/utils_3.c		\
			./srcs/utils_2.c		\
			# ./srcs/ft_split.c		\

OBJS = ${SRCS:.c=.o}

CC = gcc

CFLAGS = -Wall -Wextra -Werror -g3 -I ${INCS}

RM = rm -f

all : ${NAME}

%.o: %.c ${INCS}
	${CC} ${CFLAGS} -c $< -o $@

${NAME}: ${OBJS}
	${CC} ${OBJS} -o ${NAME}

clean:
	${RM} ${OBJS}

fclean: clean
	${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re