
NAME        := philo
CC        := gcc
FLAGS    := -Wall -Wextra -Werror -fsanitize=thread -g

SRCS        :=      utils.c \
                          main.c \
						  init_structs.c \
						  philo_actions.c \
						  check_data.c \
						  check_assign_dead.c

OBJS        := $(SRCS:.c=.o)

.c.o:
	${CC} ${FLAGS} -c $< -o ${<:.c=.o}


RM		    := rm -f

${NAME}:	${OBJS}
			${CC} ${FLAGS} -o ${NAME} ${OBJS}


all:		${NAME}

bonus:		all

clean:
			@ ${RM} *.o */*.o */*/*.o

fclean:		clean
			@ ${RM} ${NAME}

re:			fclean all

.PHONY:		all clean fclean re


