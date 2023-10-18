CC = cc

# SANITIZE = -fsanitize=address
CFLAG = -Wall -Werror -Wextra -g $(SANITIZE)

NAME = pipex

SRCS = main.c input.c fork.c pipe.c init.c print.c

SRCS_BONUS = ./bonus/main_bonus.c ./bonus/input_bonus.c ./bonus/fork_bonus.c \
			./bonus/pipe_bonus.c ./bonus/read_line_bonus.c ./bonus/read_line_bonus2.c \
			./bonus/print_bonus.c

OBJS = $(SRCS:.c=.o)

OBJS_BONUS = $(SRCS_BONUS:.c=.o)

LIBFT_DIR = ./libft/ 

all : $(NAME)

$(NAME) : $(OBJS)
		make all -C $(LIBFT_DIR)
		$(CC) $(CFLAG) -L./libft -lft $(OBJS) -o $(NAME)

%.o : %.c
	 $(CC) $(CFLAG) -c $^ -o $@

bonus : $(OBJS_BONUS)
		make all -C $(LIBFT_DIR)
		$(CC) $(CFLAG) -L./libft -lft $(OBJS_BONUS) -o $(NAME)

clean : 
		rm -rf $(OBJS)
		rm -rf $(OBJS_BONUS)
		make fclean -C $(LIBFT_DIR)

fclean : clean 
	    rm -rf $(NAME)
		make fclean -C $(LIBFT_DIR)

re : fclean all

.PHONY : all clean fclean re
