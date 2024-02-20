NAME	:= so_long

# colors
RED = \033[0;31m
GREEN = \033[0;32m
RESET = \033[0m

CFLAGS	:= -Wextra -Wall -Werror -Wunreachable-code -Ofast -g -v

# libs
LIBMLX	:= ./MLX42
LIBFTPATH = ./libft/
LIBFT = $(LIBFTPATH)libft.a

HEADERS	:= -I ./include -I $(LIBMLX)/include
LIBS	:= $(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm


SRCS	:=		src/main.c				src/check_map.c \
				src/init_map.c 			src/movement.c \
				src/load_and_free.c		src/utils.c \
				src/read_map.c

SRCSB	:=		src/bonus.c				src/check_map.c \
				src/init_map.c 			src/movement.c \
				src/load_and_free.c		src/utils.c \
				src/read_map.c			src/enemy.c

OBJS	:= ${SRCS:.c=.o}

OBJSB	:= ${SRCSB:.c=.o}

%.o: %.c
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS)

all: libmlx $(NAME)

$(NAME): $(OBJS) $(LIBMLX)
	@echo "$(RED)Building $(NAME)...$(RESET)"
	@make -C libft -s
	@$(CC) $(OBJS) $(LIBS) $(LIBFT) $(HEADERS) -o $(NAME)
	@echo "$(GREEN)$(NAME) built$(RESET)"

libmlx:
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4

bonus: $(OBJSB) $(LIBMLX)
	@echo "$(RED)Building $(NAME)...$(RESET)"
	@make -C libft -s
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4
	@$(CC) $(OBJSB) $(LIBS) $(LIBFT) $(HEADERS) -o $(NAME)
	@echo "$(GREEN)$(NAME) built$(RESET)"

clean:
	@rm -rf $(OBJS)
	@rm -rf $(OBJSB)
	@rm -rf $(LIBMLX)/build
	@make -C $(LIBFTPATH) clean -s

fclean: clean
	@rm -rf $(NAME)
	@make -C $(LIBFTPATH) fclean -s

re: fclean all

.PHONY: all, clean, fclean, re, libmlx