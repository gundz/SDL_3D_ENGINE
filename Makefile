NAME = Project

CC =  gcc
CFLAGS = -Wall -Wextra -Werror -o3 -g -lm
CFLAGS += `sdl2-config --cflags`

LFLAGS += `sdl2-config --libs`

#CFLAGS += -I /usr/include/SDL2
#LFLAGS += -lSDL2_image

PATH_INC = includes/
PATH_OBJ = obj
PATH_SRC = src

LIB_PATH = Libft/
LIB_INC = $(LIB_PATH)includes
LIB_NAME = libft.a

SRC =		\
			sdl_init.c \
			sdl_events.c \
			sdl_fps_counter.c \
			sdl_draw.c \
			sdl_color.c \
			sdl_surface.c \
			3d_tools.c \
			math_tools.c \
			object.c \
			wireframeView.c \
			dotView.c \
			get_next_line.c \
			event.c \

SRC +=	main.c

OBJ = $(patsubst %.c, $(PATH_OBJ)/%.o, $(SRC))

all: lib $(NAME)

$(NAME): namemes $(OBJ)
	@ $(CC) $(OBJ) $(CFLAGS) $(LFLAGS) -I $(PATH_INC) -I $(LIB_INC) $(LIB_PATH)$(LIB_NAME) -o $(NAME)
	@ echo " \033[4m\033[95md\033[93mo\033[32mn\033[96me \033[91m!\033[0m"

$(PATH_OBJ)/%.o: $(addprefix $(PATH_SRC)/, %.c)
	@ echo -n .
	@ mkdir -p $(PATH_OBJ)
	@ $(CC) -c $^ -I $(PATH_INC) -I $(LIB_INC) $(CFLAGS) $(LFGLAGS) -o $@

lib:
	@ make -C $(LIB_PATH)

clean:
	@ make clean -C $(LIB_PATH)
	@ rm -rf $(PATH_OBJ)
	@ echo "Cleaning $(NAME) \
		\033[4m\033[95md\033[93mo\033[32mn\033[96me \033[91m!\033[0m"

fclean: clean
	@ make fclean -C $(LIB_PATH)
	@ rm -rf $(NAME)
	@ echo "Fcleaning $(NAME) \
		\033[4m\033[95md\033[93mo\033[32mn\033[96me \033[91m!\033[0m"

namemes :
	@ echo -n Compiling $(NAME)

re: fclean all

.PHONY: clean fclean re lib
