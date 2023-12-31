# Project properties
NAME := cub3D
SRCS_DIR := src
BUILD_DIR := build
BREW := $(shell brew --prefix)
LIBFT := lib/libft
MLX42 := lib/mlx42/build

# Compilation settings
CC := cc #compiler
CFLAGS := -Wextra -Wall -Werror -Ofast
CFLAGS += -Iinclude -Ilib/mlx42/include -I$(LIBFT) #includes
LIBS := -L$(MLX42) -lmlx42 #MLX42
LIBS += -L$(BREW)/Cellar/glfw/3.3.8/lib -lglfw #GLFW
LIBS += -L$(LIBFT) -lft #libft
LIBS += -lm #math

# Source files
SRCS := $(addprefix $(SRCS_DIR)/,\
	main.c\
	utils.c\
	hooks.c\
	free.c\
	background/background.c\
	background/sky.c\
	parser/parser.c\
	parser/params.c\
	parser/map.c\
	parser/validity.c\
	parser/utils.c\
	minimap/minimap.c\
	raycast/raycast.c\
	raycast/draw.c\
	raycast/dda.c\
)
OBJS := $(patsubst $(SRCS_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRCS))
OBJS_DIRS := $(sort $(dir $(OBJS)))

# Main rule
all: $(MLX42)/libmlx42.a $(LIBFT)/libft.a $(OBJS_DIRS) $(NAME)

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
	@cmake lib/mlx42 -B $(MLX42)
	@make -C $(MLX42) -j4

$(LIBFT)/libft.a:
	@make -C $(LIBFT)

# Clean rules
clean:
	@rm -rf $(BUILD_DIR)

fclean: clean
	@echo [$(NAME)]: cleaned
	@rm -f $(NAME)
	@rm -f $(LIBFT)/libft.a
	@rm -rf $(MLX42)

# Other rules
re: fclean all
.PHONY: all clean fclean re
-include $(OBJS:.o=.d)
