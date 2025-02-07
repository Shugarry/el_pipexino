NAME = libft.a
HEADERS = libft.h get_next_line.h get_next_line_bonus.h ft_printf.h
SRC = ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c ft_isascii.c\
ft_isdigit.c ft_isprint.c ft_itoa.c ft_memchr.c ft_memcmp.c ft_memcpy.c\
ft_memmove.c ft_memset.c ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c\
ft_putstr_fd.c ft_split.c ft_strchr.c ft_strdup.c ft_striteri.c ft_strjoin.c\
ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strmapi.c ft_strncmp.c ft_strnstr.c\
ft_strrchr.c ft_strtrim.c ft_substr.c ft_tolower.c ft_toupper.c ft_printf.c\
print_base.c print_uns.c print_ptr.c print_str.c print_char.c get_next_line.c\
ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c\
ft_lstlast_bonus.c ft_lstadd_back_bonus.c ft_lstdelone_bonus.c\
ft_lstclear_bonus.c ft_lstiter_bonus.c ft_lstmap_bonus.c get_next_line_bonus.c\
get_next_line_utils_bonus.c get_next_line_utils.c

OBJ = $(SRC:.c=.o)

COMPILE = cc -Wall -Wextra -Werror -c

LIB = ar rc $(NAME)

all: $(NAME)

$(NAME): $(OBJ) $(HEADERS) Makefile 	
	@$(COMPILE) $(SRC)
	@$(LIB) $(OBJ)

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all
	
.PHONY: all re clean fclean
