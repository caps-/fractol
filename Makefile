#program name
NAME	= fractol

#directories
SRCDIR	= ./src
INCDIR	= ./include
OBJDIR	= ./obj

#source files
SRC		= fractol.c \
		  colour.c \
		  formulas.c \
		  init.c \
		  keys.c \
		  mouse.c

#object files
OBJ		= $(addprefix $(OBJDIR)/,$(SRC:.c=.o))

#compiler
CC		= gcc
CFLAGS	= -Wall -Wextra -Werror -g -O2

#minilibx
MLX		= ./mlx/
MLX_LNK	= -L $(MLX) -l mlx -framework OpenGL -framework AppKit
MLX_INC	= -I $(MLX)
MLX_LIB	= $(addprefix $(MLX),mlx.a)

#libft
FT		= ./libft/
FT_LIB	= $(addprefix $(FT),libft.a)
FT_INC	= -I ./libft
FT_LNK	= -L ./libft -l ft


#all the things we're going to compile
all: obj $(FT_LIB) $(MLX_LIB) $(NAME)

#make a directory for the object files
obj:
	mkdir -p $(OBJDIR)

#compile objects outta the sources and headers 
$(OBJDIR)/%.o:$(SRCDIR)/%.c
	$(CC) $(CFLAGS) $(MLX_INC) $(FT_INC) -I $(INCDIR) -o $@ -c $<

#compile libft
$(FT_LIB):
	@make -C $(FT)

#compile minilibx
$(MLX_LIB):
	@make -C $(MLX)

#compile everything all together as well as link the libft and minilibx libs
$(NAME): $(OBJ)
	$(CC) $(OBJ) $(MLX_LNK) $(FT_LNK) -lm -o $(NAME)

#clean that shit up
clean:
	rm -rf $(OBJDIR)
	make -C $(FT) clean
	make -C $(MLX) clean

fclean: clean
	rm -rf $(NAME)
	make -C $(FT) fclean

re: fclean all

.PHONY: all re clean fclean
