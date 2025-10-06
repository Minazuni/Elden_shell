NAME = libft.a
CC = cc
CFLAGS = -Wall -Wextra -Werror 

SRC = ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c \
      ft_strlen.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c \
      ft_strlcpy.c ft_strlcat.c ft_toupper.c ft_tolower.c ft_strchr.c \
      ft_strrchr.c ft_strncmp.c ft_memchr.c ft_memcmp.c ft_strnstr.c \
      ft_atoi.c ft_calloc.c ft_strdup.c ft_substr.c ft_strjoin.c \
      ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c ft_striteri.c \
      ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
      ft_strcmp.c ft_strdup.c

BONUS_SRC = ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c \
            ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c

PRINTF_SRC = ft_printf/ft_parse.c ft_printf/ft_print_char.c \
             ft_printf/ft_print_hex.c ft_printf/ft_print_int.c \
             ft_printf/ft_print_nbr.c ft_printf/ft_print_pointer.c ft_printf/ft_print_str.c \
             ft_printf/ft_print_unsigned.c ft_printf/ft_printf_format.c \
             ft_printf/ft_printf.c

GNL_SRC = Gnl/get_next_line.c Gnl/get_next_line_utils.c

SRC_ALL = $(SRC) $(PRINTF_SRC) $(GNL_SRC)
OBJ = $(SRC_ALL:.c=.o)
BONUS_OBJ = $(BONUS_SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	ar rcs $(NAME) $(OBJ)

bonus: $(OBJ) $(BONUS_OBJ)
	ar rcs $(NAME) $(OBJ) $(BONUS_OBJ)

# Compile .c to .o, creating the directory if needed
%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(BONUS_OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus
