# Project properties
NAME := cub3D
SRCS_DIR := src
BUILD_DIR := build
BREW := $(shell brew --prefix)
MLX42 := mlx42/build

# Compilation settings
CC := cc #compiler
CFLAGS := -Wextra -Wall -Wunreachable-code -Ofast #flags #TODO: add -Werror
CFLAGS += -Iinclude -Imlx42/include -Ilibft #includes
LIBS := -L$(BREW)/Cellar/glfw/3.3.8/lib/ -lglfw #GLFW
LIBS += -L$(MLX42) -lmlx42 #MLX42
LIBS += -Llibft -lft #libft

# Source files
SRCS := $(addprefix $(SRCS_DIR)/,\
	main.c\
	error.c\
	keys.c\
	parse.c\
	utils.c\
)
OBJS := $(patsubst $(SRCS_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRCS))
OBJS_DIRS := $(sort $(dir $(OBJS)))

# Main rule
all: $(MLX42)/libmlx42.a libft/libft.a $(OBJS_DIRS) $(NAME)

# Final binary rule
$(NAME): $(OBJS)
	@echo "\033[2K[$@]: compiled"
	@$(CC) $(CFLAGS) $^ -o $@ $(LIBS)

# Object files rules
$(BUILD_DIR)/%.o: $(SRCS_DIR)/%.c Makefile
	@echo "\033[2K[$(NAME)]: compiling $<\033[A"
	@$(CC) $(CFLAGS) -MMD -MP -c $< -o $@

$(OBJS_DIRS):
	@mkdir -p $@

# Dependencies rules
$(MLX42)/libmlx42.a:
	@cmake mlx42 -B $(MLX42)
	@make -C $(MLX42) -j4

libft/libft.a:
	@make -C libft

# Clean rules
clean:
	@rm -rf $(BUILD_DIR)

fclean: clean
	@echo [$(NAME)]: cleaned
	@rm -f $(NAME)
	@rm -rf $(MLX42)

# Other rules
re: fclean all
.PHONY: all clean fclean re
-include $(OBJS:.o=.d)
