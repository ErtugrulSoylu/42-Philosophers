NAME	=	philo_bonus
SRCS	=	main.c utils.c init.c life.c error.c
OBJS	=	$(SRCS:.c=.o)
CFLAGS	=	-Wall -Wextra -Werror

all: $(NAME)
$(NAME): $(OBJS)
	gcc -o $(NAME) $(OBJS) -lpthread
%.o: %.c
	gcc -c $< -o $@ $(CFLAGS)
clean:
	rm -rf $(NAME)
fclean: clean
	rm -rf $(NAME) $(OBJS)
re: fclean all
.PHONY: all, clean, fclean, re
