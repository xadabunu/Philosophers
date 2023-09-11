# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: xadabunu <xadabunu@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/22 17:58:21 by xadabunu          #+#    #+#              #
#    Updated: 2023/07/22 17:58:21 by xadabunu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	:=	philo

FILES	:=	main.c \
			actions.c \
			check_cmd.c \
			setup.c \
			utils.c

CFLAGS	=	-Wall -Wextra -Werror -pthread
LDLIBS	=	-lpthread

OBJS	:=	${FILES:.c=.o}

RM		=	rm -rf

all		:	${NAME}

${NAME}	:	${OBJS}
			${CC} ${OBJS} ${LDLIBS} -o ${NAME}

clean	:
			${RM} ${OBJS}

fclean	:	clean
			${RM} ${NAME}

re		:	fclean all

.PHONY	:	all clean fclean re m_dir