# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: afalconi <afalconi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/26 19:40:04 by ccolaiac          #+#    #+#              #
#    Updated: 2023/02/12 15:55:50 by afalconi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
SRC =	philo.c \
		check.c \
		routine.c \


OBJS = ${SRC:.c=.o}

%.o: %.c
	$(CC) $(CFLAGS) -g -c $< -o ${<:.c=.o}

CC		= gcc
RM		= rm -f
CFLAGS = -Wall -Wextra -Werror

$(NAME): ${OBJS}
		$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

all:	${NAME}

clean:
		${RM} ${OBJS}

fclean: clean
		${RM} ${NAME}

re:		fclean all

.PHONY: clean fclean re bonus
