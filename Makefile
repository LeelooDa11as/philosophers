# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kate <kate@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/28 17:36:56 by kkoval            #+#    #+#              #
#    Updated: 2024/08/29 02:12:46 by kate             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
HEADER = philo.h
SRCS = philo_start.c philo_life.c philo_utils.c philo_utils2.c
OBJS = ${SRCS:.c=.o}
CC = cc
RM = rm -f
CFLAGS = -Wall -Wextra -Werror -fsanitize=thread -g

all:        ${NAME}

%.o: %.c	Makefile ${HEADER} 
	${CC} ${CFLAGS} -c $< -o $@ #${<:.c=.o}

${NAME}:	${OBJS}
	 ${CC} ${CFLAGS} ${OBJS} -o ${NAME}

clean:
			${RM} ${OBJS}

fclean:     clean
			${RM} ${NAME}

re:         fclean all

.PHONY: all clean fclean re