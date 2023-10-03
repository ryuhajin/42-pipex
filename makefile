CC = cc

CFLAG = -Wall -Werror -Wextra -g

NAME = pipex

SRCS = main.c input.c fork.c pipe.c

OBJS = $(SRCS:.c=.o)

LIBFT_DIR = ./libft/ 

all : $(NAME)

$(NAME) : $(OBJS)
		make all -C $(LIBFT_DIR)
		$(CC) $(CFLAG) -L./libft -lft $(OBJS) -o $(NAME)

%.o : %.c
	 $(CC) $(CFLAG) -c $^ -o $@

clean : 
		rm -rf $(OBJS)
		make fclean -C $(LIBFT_DIR)

fclean : clean 
	    rm -rf $(NAME)
		make fclean -C $(LIBFT_DIR)

re : fclean all

.PHONY : all clean fclean re
