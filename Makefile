CC		= cc

CFLAGS	= -Wall -Wextra -Werror #-fsanitize=thread -g -O1
# LDFLAGS = -fsanitize=thread
HEADER	= ./inc/

NAME	= philo

SRCS	= src/main.c src/initialize.c src/routine.c src/death.c src/s_routine.c src/utils.c

OBJS	= $(SRCS:.c=.o)

GREEN	=	\e[0;32m
YELLOW	=	\e[0;33m
CYAN	=	\e[0;36m
RESET	=	\e[0m

all : $(NAME)

$(NAME) : $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@rm -f $(OBJS)
	@printf "$(GREEN)Executable created$(RESET)\n"

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJS)
	@printf "$(CYAN)Cleaning object files...$(RESET)\n"

fclean: clean
	@rm -f $(NAME)
	@printf "$(CYAN)Cleaning executables...$(RESET)\n"

re: fclean all

.PHONY: all clean fclean re