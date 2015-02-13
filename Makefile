NAME = Project

CC =  gcc
CFLAGS = -Wall -Wextra -Werror -g -lm
CFLAGS += `sdl2-config --cflags`

LFLAGS += `sdl2-config --libs`

#CFLAGS += -I /usr/include/SDL2
#LFLAGS += -lSDL2_image

PATH_INC = includes/
PATH_OBJ = obj
PATH_SRC = src

SRC =		\
			sdl_init.c \
			sdl_events.c \
			sdl_fps_counter.c \
			sdl_draw.c \
			sdl_color.c \
			sdl_surface.c \
			3d_tools.c \
			math_tools.c \

SRC +=	main.c

OBJ = $(patsubst %.c, $(PATH_OBJ)/%.o, $(SRC))

all: $(NAME)

$(NAME): namemes $(OBJ)
	@ $(CC) $(OBJ) $(CFLAGS) $(LFLAGS) -I $(PATH_INC) -o $(NAME)
	@ echo " \033[4m\033[95md\033[93mo\033[32mn\033[96me \033[91m!\033[0m"

$(PATH_OBJ)/%.o: $(addprefix $(PATH_SRC)/, %.c)
	@ echo -n .
	@ mkdir -p $(PATH_OBJ)
	@ $(CC) -c $^ -I $(PATH_INC) -I $(LIBINC) $(CFLAGS) $(LFGLAGS) -o $@

clean:
	@ rm -rf $(PATH_OBJ)
	@ echo "Cleaning $(NAME) \
		\033[4m\033[95md\033[93mo\033[32mn\033[96me \033[91m!\033[0m"

fclean: clean
	@ rm -rf $(NAME)
	@ echo "Fcleaning $(NAME) \
		\033[4m\033[95md\033[93mo\033[32mn\033[96me \033[91m!\033[0m"

namemes :
	@ echo -n Compiling $(NAME)

re: fclean all

.PHONY: clean fclean re
