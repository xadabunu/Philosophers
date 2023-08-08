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
			check_cmd.c \
			utils.c

S_DIR	=	src
B_DIR	=	build
I_DIR	=	include

SRCS	:=	${addprefix ${S_DIR}/, ${FILES}}

CFLAGS	=	-Wall -Wextra -Werror -pthread

LDFLAGS	:=	${addprefix -L, ${I_DIR}}

OBJS	:=	${SRCS:${S_DIR}/%.c=${B_DIR}/%.o}

RM		=	rm -rf

all		:	${NAME}

${NAME}	:	${OBJS}
			${CC} ${LDFLAGS} ${OBJS} ${LDLIBS} -o $@

m_dir	:
			mkdir -p ${B_DIR}

${OBJS}	:	m_dir
			${CC} ${CFLAGS} ${LDFLAGS} -c $< -o $@

clean	:
			${RM} ${B_DIR}

fclean	:	clean
			${RM} ${NAME}

re		:	fclean all

.PHONY	:	all clean fclean re m_dir