#ifndef					EASY_SDL_H
# define				EASY_SDL_H

# include				<SDL.h>

# define RX				1024
# define RY				768
# define NAME			"Engine"

typedef struct			s_input
{
	char				key[SDL_NUM_SCANCODES];
	int					m_x;
	int					m_y;
	int					m_r_x;
	int					m_r_y;
}						t_input;

typedef struct			s_engine
{
    SDL_Window          *win;
    SDL_Renderer        *ren;
    t_input             in;
}                       t_engine;

typedef struct          s_pt
{
    double              x;
    double              y;
}                       t_pt;

typedef struct			s_timer
{
	int					fps;
	int					current;
	int					update;
	char				title[128];
}						t_timer;

typedef struct          s_esdl
{
    t_engine            en;
    t_timer				fps;
}                       t_esdl;

int						init_sdl(t_esdl *esdl);

void					update_events(t_input *in);

void					fps_counter(t_esdl *esdl);

SDL_Surface				*sdl_create_surface(int width, int height);
void					put_pixel(SDL_Surface *const surf, const int x, const int y, const int color);

SDL_Color				sdl_int_to_color(int color);
int						sdl_color_to_int(SDL_Color color);

void					draw_line(SDL_Surface *surf, SDL_Rect rect, const int color);
void					draw_square(SDL_Surface *surf, const SDL_Rect rect, const int color);
void					clear_screen(SDL_Surface *surf, const int color);

#endif
