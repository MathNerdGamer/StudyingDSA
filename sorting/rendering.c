#include "rendering.h"

char *error_message[] = {"SDL Init Error: %s\n",
                         "TTF Init Error: %s\n",
                         "TTF Font Error: %s\n",
                         "SDL Window Error: %s\n",
                         "SDL Renderer Error: %s\n",
                         "SDL Surface Error: %s\n",
                         "SDL Texture Error: %s\n",
                         "FFMPEG Error: Unable to open file in ffmpeg.\n"};

void handle_error(error_type err,
                  SDL_Renderer *renderer,
                  SDL_Window *window,
                  SDL_Surface *surface,
                  SDL_Texture *texture)
{
    int error_set = 0;
    char *msg = error_message[err];
    switch( err )
    {
        case FFMPEG_ERROR:
            printf("%s", msg);
            error_set = 1;
        case TTF_FONT_ERROR:
            if( !error_set )
            {
                printf(msg, SDL_GetError());
                error_set = 1;
            }
            SDL_DestroyWindow(window);
        case WINDOW_ERROR:
            if( !error_set )
            {
                printf(msg, SDL_GetError());
                error_set = 1;
            }
            SDL_DestroyRenderer(renderer);
        case RENDERER_ERROR:
            if( !error_set )
            {
                printf(msg, SDL_GetError());
                error_set = 1;
            }
            SDL_FreeSurface(surface);
        case SURFACE_ERROR:
            if( !error_set )
            {
                printf(msg, SDL_GetError());
                error_set = 1;
            }
            SDL_DestroyTexture(texture);
        case TEXTURE_ERROR:
            if( !error_set )
            {
                printf(msg, SDL_GetError());
                error_set = 1;
            }
            TTF_Quit();
        case TTF_INIT_ERROR:
            if( !error_set )
            {
                printf(msg, SDL_GetError());
                error_set = 1;
            }
            SDL_Quit();

        case INIT_ERROR:
            if( !error_set )
            {
                printf(msg, SDL_GetError());
            }
    }

    exit(1);
}

SDL_Color get_color(color RGB)
{
    switch( RGB )
    {
        case RGB_GREEN:
        {
            return (SDL_Color){0, 255, 0, 255};
        }

        case RGB_BLUE:
        {
            return (SDL_Color){0, 0, 255, 255};
        }

        case RGB_YELLOW:
        {
            return (SDL_Color){255, 255, 0, 255};
        }

        case RGB_MAGENTA:
        {
            return (SDL_Color){255, 0, 255, 255};
        }

        case RGB_CYAN:
        {
            return (SDL_Color){0, 255, 255, 255};
        }

        case RGB_WHITE:
        {
            return (SDL_Color){255, 255, 255, 255};
        }

        case RGB_RED:
        default:
        {
            return (SDL_Color){255, 0, 0, 255};
        }
    }
}

void set_rgb(color RGB, int *r, int *g, int *b)
{
    SDL_Color c = get_color(RGB);

    *r = c.r;
    *g = c.g;
    *b = c.b;
}

void default_info(char *info_text, visualizer_t *viz)
{
    char const *default_format = "Algorithm: %s - %s Order\n"
                                 "Array Size: %d\n"
                                 "Inversions Remaining: %d (%d)\n"
                                 "Comparisons: %d\n"
                                 "Array Accesses: %d\n"
                                 "Swaps: %d\n"
                                 "Amount Sorted: %d/%d (%3.2f%%)";

    char default_info[256];
    snprintf(default_info,
             sizeof(default_info),
             default_format,
             viz->alg,
             order_title(viz),
             viz->array_size,
             viz->inversions,
             viz->original_inversions,
             viz->comparisons,
             viz->accesses,
             viz->swaps,
             viz->number_sorted,
             viz->array_size,
             100 * ( float )viz->number_sorted / viz->array_size);
    strncpy(info_text, default_info, strlen(default_info) + 1);

    if( viz->recursion_level >= 0 )
    {
        char recursion_level[128];
        snprintf(recursion_level,
                 sizeof(recursion_level),
                 "\nRecursion Level: %d",
                 viz->recursion_level);
        strncat(info_text, recursion_level, strlen(recursion_level) + 1);
    }

    if( viz->recursion_limit >= 0 )
    {
        char recursion_limit[128];
        snprintf(recursion_limit,
                 sizeof(recursion_limit),
                 " (Limit: %d)",
                 viz->recursion_limit);
        strncat(info_text, recursion_limit, strlen(recursion_limit) + 1);
    }
}

void index_info(char *info_text, int idx1, int idx2)
{
    char const *index1_format = "\nCurrent Indices: i = %d";
    char index1_info[128];

    snprintf(index1_info, sizeof(index1_info), index1_format, idx1);
    strncat(info_text, index1_info, strlen(index1_info) + 1);

    if( idx2 != -1 )
    {
        char const *index2_format = ", j = %d";
        char index2_info[128];

        snprintf(index2_info, sizeof(index2_info), index2_format, idx2);
        strncat(info_text, index2_info, strlen(index2_info) + 1);
    }
}

void init_SDL(char *title, char *font_path, visualizer_t *viz)
{
    if( SDL_Init(SDL_INIT_VIDEO) )
    {
        handle_error(INIT_ERROR, viz->renderer, viz->window, nullptr, nullptr);
    }

    if( TTF_Init() )
    {
        handle_error(
            TTF_INIT_ERROR, viz->renderer, viz->window, nullptr, nullptr);
    }

    Uint32 flags = SDL_WINDOW_SHOWN;

    if( viz->fullscreen )
    {
        flags = SDL_WINDOW_FULLSCREEN;
    }

    viz->window = SDL_CreateWindow(title,
                                   SDL_WINDOWPOS_UNDEFINED,
                                   SDL_WINDOWPOS_UNDEFINED,
                                   viz->screen_width,
                                   viz->screen_height,
                                   flags);

    if( !viz->window )
    {
        handle_error(
            WINDOW_ERROR, viz->renderer, viz->window, nullptr, nullptr);
    }

    viz->renderer =
        SDL_CreateRenderer(viz->window, -1, SDL_RENDERER_ACCELERATED);

    if( !viz->renderer )
    {
        handle_error(
            RENDERER_ERROR, viz->renderer, viz->window, nullptr, nullptr);
    }

    int font_size = viz->screen_height / 50;

    viz->font = TTF_OpenFont(font_path, font_size);
    if( !viz->font )
    {
        handle_error(
            TTF_FONT_ERROR, viz->renderer, viz->window, nullptr, nullptr);
    }
}

bar_config_t configure_bar(visualizer_t *viz)
{
    float bar_width = (( float )viz->screen_width) / viz->array_size;

    return (bar_config_t){bar_width, -1, -1};
}

SDL_Rect build_bar(visualizer_t *viz, bar_config_t *bar_config)
{
    return (SDL_Rect){bar_config->index * bar_config->bar_width,
                      viz->screen_height - floor(bar_config->bar_height),
                      ceil(bar_config->bar_width),
                      ceil(bar_config->bar_height)};
}

void calculate_height(visualizer_t *viz, bar_config_t *bar_config)
{
    bar_config->bar_height =
        ceil((0.75 * viz->array[bar_config->index] * viz->screen_height) /
             viz->array_size);
}

void draw_array(visualizer_t *viz)
{
    update_array(viz, RGB_WHITE, -1, -1);
    render_second(viz);
}

void update_array(visualizer_t *viz, color bar_color, int idx1, int idx2)
{
    update_array_no_present(viz, bar_color, idx1, idx2);
    SDL_RenderPresent(viz->renderer);
    export_video_frame(viz);
}

void update_array_with_alert(visualizer_t *viz,
                             color bar_color,
                             int idx1,
                             int idx2,
                             color text_color,
                             char *msg)
{
    update_array_no_present(viz, bar_color, idx1, idx2);
    text_alert(viz, text_color, msg);
    export_video_frame(viz);
}

void update_array_no_present(visualizer_t *viz,
                             color bar_color,
                             int idx1,
                             int idx2)
{
    inversion_count(viz);

    SDL_SetRenderDrawColor(viz->renderer, 0, 0, 0, 255);
    SDL_RenderClear(viz->renderer);

    bar_config_t bar_config = configure_bar(viz);
    SDL_Rect bar;

    viz->number_sorted = 0;

    for( int i = 0; i < viz->array_size; i++ )
    {
        if( viz->array[i] == viz->sorted_array[i] )
        {
            ++viz->number_sorted;
            SDL_SetRenderDrawColor(viz->renderer, 0, 255, 0, 255);
        }
        else
        {
            SDL_SetRenderDrawColor(viz->renderer, 255, 255, 255, 255);
        }
        bar_config.index = i;
        calculate_height(viz, &bar_config);
        bar = build_bar(viz, &bar_config);
        SDL_RenderFillRect(viz->renderer, &bar);
    }

    char info_text[1024];

    default_info(info_text, viz);

    if( idx1 != -1 || idx2 != -1 )
    {
        index_info(info_text, idx1, idx2);

        int r, g, b;
        set_rgb(bar_color, &r, &g, &b);

        SDL_SetRenderDrawColor(viz->renderer, r, g, b, 255);

        bar_config.index = idx1;
        calculate_height(viz, &bar_config);
        bar = build_bar(viz, &bar_config);
        bar = build_bar(viz, &bar_config);
        SDL_RenderFillRect(viz->renderer, &bar);

        if( idx1 != idx2 && idx2 != -1 )
        {
            bar_config.index = idx2;
            calculate_height(viz, &bar_config);
            bar = build_bar(viz, &bar_config);
            SDL_RenderFillRect(viz->renderer, &bar);
        }
    }

    SDL_Color color = {0, 255, 255, 255};

    SDL_Surface *text_surface = TTF_RenderText_Blended_Wrapped(
        viz->font, info_text, color, viz->screen_width);
    if( !text_surface )
    {
        handle_error(
            SURFACE_ERROR, viz->renderer, viz->window, text_surface, nullptr);
    }

    SDL_Texture *text_texture =
        SDL_CreateTextureFromSurface(viz->renderer, text_surface);
    if( !text_texture )
    {
        handle_error(TEXTURE_ERROR,
                     viz->renderer,
                     viz->window,
                     text_surface,
                     text_texture);
    }

    SDL_Rect text_rect = {10, 10, text_surface->w, text_surface->h};
    SDL_RenderCopy(viz->renderer, text_texture, NULL, &text_rect);

    SDL_DestroyTexture(text_texture);
    SDL_FreeSurface(text_surface);
}

void text_alert(visualizer_t *viz, color RGB, char *message)
{
    SDL_Color text_color = get_color(RGB);

    SDL_Surface *text_surface =
        TTF_RenderText_Blended(viz->font, message, text_color);
    if( !text_surface )
    {
        handle_error(
            SURFACE_ERROR, viz->renderer, viz->window, text_surface, nullptr);
    }

    SDL_Texture *text_texture =
        SDL_CreateTextureFromSurface(viz->renderer, text_surface);
    if( !text_texture )
    {
        handle_error(TEXTURE_ERROR,
                     viz->renderer,
                     viz->window,
                     text_surface,
                     text_texture);
    }

    int text_width = text_surface->w;
    int text_height = text_surface->h;

    SDL_Rect text_rect = {(viz->screen_width - text_width) / 2,
                          0.15 * viz->screen_height,
                          text_width,
                          text_height};

    SDL_SetRenderDrawBlendMode(viz->renderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(viz->renderer, 0, 0, 0, 200);

    SDL_RenderCopy(viz->renderer, text_texture, NULL, &text_rect);

    SDL_RenderPresent(viz->renderer);

    SDL_FreeSurface(text_surface);
    SDL_DestroyTexture(text_texture);
}

void export_video_frame(visualizer_t *viz)
{
    if( !viz->video )
    {
        return;
    }

    int screen_width, screen_height;
    SDL_GetRendererOutputSize(viz->renderer, &screen_width, &screen_height);

    SDL_RenderReadPixels(viz->renderer,
                         NULL,
                         SDL_PIXELFORMAT_RGBA32,
                         viz->pixels,
                         screen_width * 4);

    fwrite(viz->pixels, 1, screen_width * screen_height * 4, viz->ffmpeg);
}

void render_frames(visualizer_t *viz, int frames)
{
    for( int i = 0; i < frames; ++i )
    {
        export_video_frame(viz);
    }
}

void render_second(visualizer_t *viz)
{
    render_frames(viz, ceil(viz->framerate));
}
