NAME = wolf3d

CC = clang

CFLAGS = -Wall -Werror -Wextra -g3 -fsanitize=address

LFLAGS = -Llibft -lft -L$(MINILIB) -lmlx

DIR = srcs

LIB = lib

SRCS = main.c		parse.c	hook.c	move.c	init.c	minimap.c	raycast.c	\
	   texture.c

SRC = $(addprefix $(DIR)/,$(SRCS))

OBJ = $(SRCS:.c=.o)

INC = includes 
LIBINC = libft/includes

all: $(NAME)

$(NAME): $(LIB) $(OBJ) Makefile
	@$(CC) $(CFLAGS) $(OBJ) $(LFLAGS) -o $(NAME) $(ADDS)

$(LIB): $(MINILIB)
	@make -C libft
	@make -C $(MINILIB)

$(OBJ): $(SRC) $(INC)
	@$(CC) $(CFLAGS) -c $(SRC) -I $(INC) -I $(LIBINC) -I $(MINILIB)

MINILIB: $(UNAME_S)

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
	CC = gcc
	MINILIB = minilibx
	ADDS = -L/usr/X11/lib -lXext -lX11
endif
ifeq ($(UNAME_S),Darwin)
	ADDS = -framework OpenGl -framework AppKit
	UNAME_R := $(shell uname -r)
	ifneq ($(filter 15%, $(UNAME_R)),)
		MINILIB = minilibx_macos_el_capitan
	endif
	ifneq ($(filter 16%, $(UNAME_R)),)
		MINILIB = minilibx_macos_sierra
	endif
endif

clean:
	@rm -rf $(OBJ)
	@rm -f *.gch
	@make -C libft clean
	@make -C $(MINILIB) clean

fclean: clean
	@rm -f $(NAME)
	@make -C libft fclean
	@make -C $(MINILIB) clean

re: fclean all

