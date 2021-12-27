SRCS		= utils.c action.c init.c init_utils.c main.c time.c \

OBJS			= $(SRCS:.c=.o)

NAME			= philo

CFLAGS			= -Wall -Wextra -Werror -g -pthread 

RM				= rm -f

CC				= cc

AR				= ar rcs

OBJ_DIR = obj

.c.o:
				$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

$(NAME):		$(OBJS)
				$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -L.



all:			$(NAME)

clean:
				$(RM) $(OBJS) 

fclean:			clean
				$(RM) $(NAME)

re:				fclean all

.PHONY:			all clean fclean c.o re 