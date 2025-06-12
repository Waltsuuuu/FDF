# Compiler
CC = cc
CFLAGS = -Wall -Wextra -Werror -Iincludes

# Executable
NAME = fdf

# === LIBFT ===
LIBFT_DIR = libft
LIBFT_SRCS = \
	$(LIBFT_DIR)/ft_atoi.c \
	$(LIBFT_DIR)/ft_bzero.c \
	$(LIBFT_DIR)/ft_calloc.c \
	$(LIBFT_DIR)/ft_isalnum.c \
	$(LIBFT_DIR)/ft_isalpha.c \
	$(LIBFT_DIR)/ft_isascii.c \
	$(LIBFT_DIR)/ft_isdigit.c \
	$(LIBFT_DIR)/ft_isprint.c \
	$(LIBFT_DIR)/ft_itoa.c \
	$(LIBFT_DIR)/ft_memchr.c \
	$(LIBFT_DIR)/ft_memcmp.c \
	$(LIBFT_DIR)/ft_memcpy.c \
	$(LIBFT_DIR)/ft_memmove.c \
	$(LIBFT_DIR)/ft_memset.c \
	$(LIBFT_DIR)/ft_putchar_fd.c \
	$(LIBFT_DIR)/ft_putendl_fd.c \
	$(LIBFT_DIR)/ft_putnbr_fd.c \
	$(LIBFT_DIR)/ft_putstr_fd.c \
	$(LIBFT_DIR)/ft_split.c \
	$(LIBFT_DIR)/ft_strchr.c \
	$(LIBFT_DIR)/ft_strdup.c \
	$(LIBFT_DIR)/ft_striteri.c \
	$(LIBFT_DIR)/ft_strjoin.c \
	$(LIBFT_DIR)/ft_strlcat.c \
	$(LIBFT_DIR)/ft_strlcpy.c \
	$(LIBFT_DIR)/ft_strlen.c \
	$(LIBFT_DIR)/ft_strmapi.c \
	$(LIBFT_DIR)/ft_strncmp.c \
	$(LIBFT_DIR)/ft_strnstr.c \
	$(LIBFT_DIR)/ft_strrchr.c \
	$(LIBFT_DIR)/ft_strtrim.c \
	$(LIBFT_DIR)/ft_substr.c \
	$(LIBFT_DIR)/ft_tolower.c \
	$(LIBFT_DIR)/ft_toupper.c \
	$(LIBFT_DIR)/ft_lstadd_back_bonus.c \
	$(LIBFT_DIR)/ft_lstadd_front_bonus.c \
	$(LIBFT_DIR)/ft_lstclear_bonus.c \
	$(LIBFT_DIR)/ft_lstdelone_bonus.c \
	$(LIBFT_DIR)/ft_lstiter_bonus.c \
	$(LIBFT_DIR)/ft_lstlast_bonus.c \
	$(LIBFT_DIR)/ft_lstmap_bonus.c \
	$(LIBFT_DIR)/ft_lstnew_bonus.c \
	$(LIBFT_DIR)/ft_lstsize_bonus.c

# === GNL ===
GNL_DIR = get_next_line
GNL_SRCS = \
	$(GNL_DIR)/get_next_line.c \
	$(GNL_DIR)/get_next_line_utils.c

# === FDF ===
SRC_DIR = src
FDF_SRCS = \
	$(SRC_DIR)/main.c

# === OBJS ===
SRCS = $(FDF_SRCS) $(GNL_SRCS) $(LIBFT_SRCS)
OBJS = $(SRCS:.c=.o)

# === RULES ===
all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
