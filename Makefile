# === Compiler & Flags ===
CC = cc
CFLAGS = -Wall -Wextra -Werror -Iincludes -I$(MLX_DIR)

# === Executable ===
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

# === PRINTF ===
PRINTF_DIR = printf
PRINTF_SRCS = \
	$(PRINTF_DIR)/ft_printf.c \
	$(PRINTF_DIR)/ft_printf_utils.c

# === FDF ===
SRC_DIR = src
FDF_SRCS = \
	$(SRC_DIR)/main.c \
	$(SRC_DIR)/01_parse/parse_map.c \
	$(SRC_DIR)/01_parse/parse_map_utils.c \
	$(SRC_DIR)/01_parse/parse_map_row_utils.c \
	$(SRC_DIR)/02_initialize/init_mlx.c \
	$(SRC_DIR)/03_transform/scale_and_offset.c \
	$(SRC_DIR)/04_render/draw_pixel.c \
	$(SRC_DIR)/04_render/draw_line.c \
	$(SRC_DIR)/04_render/draw_map.c \
	$(SRC_DIR)/04_render/projection.c \
	$(SRC_DIR)/05_controls/hooks.c \
	$(SRC_DIR)/06_cleanup/cleanup.c

# === MLX ===
MLX_DIR := minilibx-linux
MLX_LIB := $(MLX_DIR)/libmlx_Linux.a
MLX_FLAGS := -L$(MLX_DIR) -lmlx -lXext -lX11 -lm -lz

# === OBJS ===
SRCS = $(FDF_SRCS) $(GNL_SRCS) $(LIBFT_SRCS) $(PRINTF_SRCS)
OBJS = $(SRCS:.c=.o)

# === Build Targets ===
all: $(NAME)

$(NAME): $(OBJS) $(MLX_LIB)
	$(CC) $(CFLAGS) $(OBJS) $(MLX_LIB) $(MLX_FLAGS) -o $(NAME)

$(MLX_LIB):
	$(MAKE) -C $(MLX_DIR)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# === Cleanup ===
clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(MLX_DIR) clean

re: fclean all

.PHONY: all clean fclean re
