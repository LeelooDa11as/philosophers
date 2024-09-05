# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kkoval <kkoval@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/28 17:36:56 by kkoval            #+#    #+#              #
#    Updated: 2024/09/05 16:15:38 by kkoval           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
HEADER = philo.h
SRCS = philo_start.c philo_life.c philo_utils.c philo_free.c philo_arg_check.c \
		philo_utils2.c
OBJS = ${SRCS:.c=.o}
CC = cc
RM = rm -f
CFLAGS = -Wall -Wextra -Werror -g -fsanitize=thread

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