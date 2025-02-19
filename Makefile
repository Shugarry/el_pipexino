COMPILE = cc -Wall -Wextra -Werror# -g

NAME = pipex

SRC = srcs/main.c \

OBJ = $(SRC:.c=.o)

#=======================TO MAKE SURE MAKEFILE RECOMPILES=======================#

LIB_DEP = \
libft/ft_atoi.c \
libft/ft_bzero.c \
libft/ft_calloc.c \
libft/ft_isalnum.c \
libft/ft_isalpha.c \
libft/ft_isascii.c \
libft/ft_isdigit.c \
libft/ft_isprint.c \
libft/ft_itoa.c \
libft/ft_memchr.c \
libft/ft_memcmp.c \
libft/ft_memcpy.c \
libft/ft_memmove.c \
libft/ft_memset.c \
libft/ft_putchar_fd.c \
libft/ft_putendl_fd.c \
libft/ft_putnbr_fd.c \
libft/ft_putstr_fd.c \
libft/ft_split.c \
libft/ft_strchr.c \
libft/ft_strdup.c \
libft/ft_striteri.c \
libft/ft_strjoin.c \
libft/ft_strlcat.c \
libft/ft_strlcpy.c \
libft/ft_strlen.c \
libft/ft_strmapi.c \
libft/ft_strncmp.c \
libft/ft_strnstr.c \
libft/ft_strrchr.c \
libft/ft_strtrim.c \
libft/ft_substr.c \
libft/ft_tolower.c \
libft/ft_toupper.c \
libft/ft_printf.c \
libft/print_base.c \
libft/print_uns.c \
libft/print_ptr.c \
libft/print_str.c \
libft/print_char.c \
libft/get_next_line.c \
libft/ft_lstnew_bonus.c \
libft/ft_lstadd_front_bonus.c \
libft/ft_lstsize_bonus.c \
libft/ft_lstlast_bonus.c \
libft/ft_lstadd_back_bonus.c \
libft/ft_lstdelone_bonus.c \
libft/ft_lstclear_bonus.c \
libft/ft_lstiter_bonus.c \
libft/ft_lstmap_bonus.c \
libft/get_next_line_bonus.c \
libft/get_next_line_utils_bonus.c \
libft/get_next_line_utils.c \

OBJ_DEP = $(LIB_DEP:.c=.o)

ALL_DEP = Makefile pipex.h $(OBJ) $(LIB_DEP) $(OBJ_DEP) libft/Makefile

#=======================TO MAKE SURE MAKEFILE RECOMPILES=======================#

all: $(NAME)

$(NAME): $(ALL_DEP)
	@make all -C libft
	@$(COMPILE) $(SRC) ./libft/libft.a -o $(NAME) 

clean:
	@make clean -C libft
	@rm -f $(OBJ)

fclean: clean
	@make fclean -C libft
	@rm -f $(NAME)
	@echo 'all clean!! :)'

re: fclean all

.PHONY: all re clean fclean
