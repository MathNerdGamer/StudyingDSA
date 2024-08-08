#ifndef MATH_NERD_SORTING_RENDERING_H
#define MATH_NERD_SORTING_RENDERING_H
#include <quiet_vscode.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "utility.h"

typedef enum
{
    RGB_RED,
    RGB_GREEN,
    RGB_BLUE,
    RGB_YELLOW,
    RGB_MAGENTA,
    RGB_CYAN,
    RGB_WHITE
} color;

typedef enum
{
    INIT_ERROR,
    TTF_INIT_ERROR,
    TTF_FONT_ERROR,
    WINDOW_ERROR,
    RENDERER_ERROR,
    SURFACE_ERROR,
    TEXTURE_ERROR,
    FFMPEG_ERROR
} error_type;

typedef struct
{
    float bar_width;
    float bar_height;
    int index;
} bar_config_t;

void handle_error(
    error_type, SDL_Renderer *, SDL_Window *, SDL_Surface *, SDL_Texture *);
void set_rgb(color, int *, int *, int *);
SDL_Color get_color(color);

void init_SDL(char *, char *, visualizer_t *);

bar_config_t configure_bar(visualizer_t *);
SDL_Rect build_bar(visualizer_t *, bar_config_t *);
void calculate_height(visualizer_t *, bar_config_t *);

void draw_array(visualizer_t *);
void update_array(visualizer_t *, color, int, int);
void update_array_with_alert(visualizer_t *, color, int, int, color, char *);
void update_array_no_present(visualizer_t *, color, int, int);

void text_alert(visualizer_t *, color, char *);
void export_video_frame(visualizer_t *);
void render_frames(visualizer_t *, int);
void render_second(visualizer_t *);

#endif // MATH_NERD_SORTING_RENDERING_H