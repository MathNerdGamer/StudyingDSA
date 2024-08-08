#ifndef MATH_NERD_SORTING_UTILITY_H
#define MATH_NERD_SORTING_UTILITY_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

typedef struct
{
    SDL_Renderer *renderer;
    SDL_Window *window;
    TTF_Font *font;

    int screen_width;
    int screen_height;
    int video;
    int random;
    int sorted;
    int fullscreen;
    int print;
    float framerate;
    char ffmpeg_command[256];
    FILE *ffmpeg;
    char alg[64];

    int *array;
    int *original_array;
    int *sorted_array;
    int array_size;
    int original_inversions;
    int inversions;
    int comparisons;
    int accesses;
    int swaps;
    int number_sorted;
    int recursion_level;
    int recursion_limit;

    int *pixels;
} visualizer_t;

void swap(visualizer_t *, int, int);

void set_to_variable(int *, visualizer_t *, int);
void set_from_variable(int, visualizer_t *, int);
int compare_variable(int, visualizer_t *, int);

void set_at_index(visualizer_t *, int, int);
int compare_indices(visualizer_t *, int, int);

void set_to_subarray(int *, int, visualizer_t *, int);
void set_from_subarray(int *, int, visualizer_t *, int);
int compare_subarrays(visualizer_t *, int *, int, int *, int);

float fraction_to_float(char *);
void shuffle_array(visualizer_t *);
void inversion_count(visualizer_t *);

int find_index(visualizer_t *, int);

char const *order_title(visualizer_t *);
char const *lower_order_title(visualizer_t *);

#define MIN(a, b) (((a) < (b)) ? (a) : (b))

#endif // MATH_NERD_SORTING_UTILITY_H