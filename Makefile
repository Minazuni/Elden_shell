# **************************************************************************** #
#                                  ELDEN SHELL                                  #
# **************************************************************************** #

NAME        = elden_shell

CC          = cc
CFLAGS      = -Wall -Wextra -Werror -g
RM          = rm -f

LIBFT_DIR   = libft
LIBFT       = $(LIBFT_DIR)/libft.a

SRC         = elden_shell.c \
              lexing.c \
              parsing.c \
              parsing_utils.c \
			  execution.c \
			  redirection.c \
			  utils.c

OBJ         = $(SRC:.c=.o)

# ----------------- RULES -----------------

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME)

%.o: %.c elden_shell.h
	$(CC) $(CFLAGS) -I. -I$(LIBFT_DIR) -c $< -o $@

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

clean:
	$(RM) $(OBJ)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	$(RM) $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
