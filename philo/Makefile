# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gghaya <gghaya@student.1337.ma>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/25 14:12:43 by gghaya            #+#    #+#              #
#    Updated: 2023/07/13 18:21:25 by gghaya           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CC = cc
FLAGS =  -Wall -Werror -Wextra -pthread -fsanitize=thread -g
CFILES = ft_atoi.c main.c ft_lstadd_back.c ft_lstnew.c \
		utils.c extra.c utils2.c

OFILES = ${CFILES:.c=.o}

all : ${NAME}

${NAME} : ${OFILES} philo.h ${CFILES}
	${CC}  ${FLAGS} ${OFILES}  -o  ${NAME}

%.o:%.c philo.h
	${CC} -c ${FLAGS} $<

clean :
	rm -f ${OFILES}

fclean : clean
	rm -f ${NAME}

re : fclean all

.PHONY: clean fclean re all