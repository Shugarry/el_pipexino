COMPILE = cc -Wall -Wextra -Werror -g
NAME = pipex
SRC = srcs/pipex.c
OBJ = $(SRC:.c=.o)
all: $(NAME)

$(NAME): Makefile pipex.h $(OBJ)
	@make all -C libft
	@$(COMPILE) $(SRC) ./libft/libft.a -o $(NAME) 
clean:
	@make clean -C libft
	@rm -f $(OBJ)
	@echo 'all clean!! :)'

fclean: clean
	@make fclean -C libft
	@rm -f $(NAME)
	@echo 'all clean!! :)'

re: fclean all

.PHONY: all re clean flclean
