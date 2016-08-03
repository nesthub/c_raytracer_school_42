NAME = RT

INCLUDES = libft/includes/

SRC = main.c\
	  error.c\
	  parse.c\
	  parse_cam.c\
	  parse_fct.c\
	  parse_col_amb.c\
	  parse_size_eff.c\
	  parse_objects.c\
	  raytracing.c\
	  ray_touch.c\
	  write_img.c\
	  mouse_functions.c\
	  key_functions.c\
	  vector_functions.c\
	  threads.c\
	  shadow_max.c\
	  write_scene.c\
	  matrice_rot.c\
	  intersec_ray.c\
	  color_functions.c\
	  perlin.c\

WFLAGS = -Wall -Werror -Wextra -O3 -march=native

LFLAGS = -L libft/ -lft -lm -lmlx -framework OpenGL -framework AppKit

CC = gcc -g

OBJ = $(SRC:.c=.o)

all : $(NAME)

%.o: %.c
	$(CC) -c $(WFLAGS) -I $(INCLUDES) $< -o $@

$(NAME) : $(OBJ)
	make -C libft
	$(CC) -o $(NAME) $(OBJ) $(WFLAGS) $(LFLAGS) -I $(INCLUDES) 

clean :
	rm -rf $(OBJ)
	make -C libft clean

img :
	@mkdir image

clean_si :
	@rm -rf image
	@rm -rf scene

fclean : clean
	rm -f $(NAME)
	make -C libft fclean

sdl_install :
	curl https://dl.dropboxusercontent.com/u/22561204/SDL/Archive.zip > /tmp/Archive.zip
	unzip -o /tmp/Archive.zip -d ~/Library/Frameworks/

re : fclean all

lre :
	make -C libft/ re

.PHONY: all clean fclean re
