#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <getopt.h>
#include <sys/stat.h>

#include "rendering.h"
#include "sorting.h"
#include "utility.h"

void create_arrays(visualizer_t *);
void alg_file_name(char *, char *);
void execute_sort_test(char *, visualizer_t *, void (*sorter)(visualizer_t *));
void print_results(char *, visualizer_t *);
void rename_video(char *, visualizer_t *);
void clean_up(visualizer_t *);

const char *help_message =
    "Usage: %s [options] [arguments]\n"

    "\t-f, --framerate <int or fraction>      Sets target video framerate "
    "(Default: 10). (optional)\n\n"

    "\t-r, --resolution [WIDTHxHEIGHT]        Sets target video resolution. "
    "(required)\n\n"

    "\t-s, --size <array_size>                Sets the size of the array to "
    "sort (Default: 10).\n\n"

    "\t-R, --random                           Enables random starting array "
    "instead of reversed.\n\n"

    "\t-S, --sorted                           Enables sorted order starting "
    "array instead of reversed.\nIf `random` toggle enabled, this does "
    "nothing.\n\n"

    "\t-F, --fullscreen                       Displays in fullscreen mode.\n\n"

    "\t-P, --print                            Prints results to a file.\n\n"

    "\t-h, --help                             Displays this message. "
    "(optional)\n";

int main(int argc, char *argv[])
{
    char *short_opts = "r:f:s:nRSFPh";
    struct option long_opts[] = {{"resolution", required_argument, NULL, 'r'},
                                 {"framerate", required_argument, NULL, 'f'},
                                 {"size", required_argument, NULL, 's'},
                                 {"novideo", no_argument, NULL, 'n'},
                                 {"random", no_argument, NULL, 'R'},
                                 {"sorted", no_argument, NULL, 'S'},
                                 {"fullscreen", no_argument, NULL, 'F'},
                                 {"print", no_argument, NULL, 'P'},
                                 {"help", no_argument, NULL, 'h'},
                                 {NULL, 0, NULL, 0}};

    int getopt_result;
    int screen_width, screen_height;
    char framerate[16] = "20";
    int video = 1;
    int array_size = 10;
    int random = 0;
    int sorted = 0;
    int fullscreen = 0;
    int print = 0;

    while( (getopt_result =
                getopt_long(argc, argv, short_opts, long_opts, NULL)) != -1 )
    {
        switch( getopt_result )
        {
            case 'f':
            {
                snprintf(framerate, sizeof(framerate), "%s", optarg);
                break;
            }

            case 'r':
            {
                char *ch = strchr(optarg, 'x');
                *ch = '\0';
                screen_width = atoi(optarg);
                char *height_string = ch + 1;
                screen_height = atoi(height_string);
                break;
            }

            case 's':
            {
                array_size = atoi(optarg);

                if( array_size < 1 )
                {
                    printf("Array size must be at least 1.\n");
                    return 1;
                }
                break;
            }

            case 'n':
            {
                video = 0;
                break;
            }

            case 'R':
            {
                random = 1;
                break;
            }

            case 'S':
            {
                sorted = 1;
                break;
            }

            case 'F':
            {
                fullscreen = 1;
                break;
            }

            case 'P':
            {
                print = 1;
                break;
            }

            case 'h':
            {
                printf(help_message, argv[0]);
                return 0;
            }
        }
    }

    visualizer_t viz = {nullptr,                      // renderer
                        nullptr,                      // window
                        nullptr,                      // font
                        screen_width,                 // width
                        screen_height,                // height
                        video,                        // video render toggle
                        random,                       // random order toggle
                        sorted,                       // sorted order toggle
                        fullscreen,                   // fullscreen toggle
                        print,                        // print toggle
                        fraction_to_float(framerate), // frame rate
                        "",                           // ffmpeg_command
                        nullptr,                      // ffmpeg
                        "",                           // alg
                        nullptr,                      // array
                        nullptr,                      // original_array
                        nullptr,                      // sorted_array
                        array_size,                   // array size
                        0,                            // inversions
                        0,                            // original inversions
                        0,                            // comparisons
                        0,                            // accesses
                        0,                            // swaps
                        0,                            // number_sorted
                        0,                            // recursion_level
                        0,                            // recursion_limit
                        nullptr};                     // pixels

    init_SDL("Sorting Visualization", "font.ttf", &viz);

    snprintf(viz.ffmpeg_command,
             sizeof(viz.ffmpeg_command),
             "ffmpeg -y -f rawvideo -pixel_format rgba -video_size %dx%d "
             "-r %s -i - -c:v libx264 -preset:v ultrafast -profile:v "
             "high444 -qp 0 -pix_fmt yuv444p -an video.mov",
             screen_width,
             screen_height,
             framerate);

    create_arrays(&viz);
    viz.pixels = malloc(screen_width * screen_height * 4);

    if( array_size <= 128 ) // O(n^2)
    {
        execute_sort_test("Bubble Sort", &viz, bubble_sort);

        execute_sort_test("Insertion Sort", &viz, insertion_sort);

        execute_sort_test("Selection Sort", &viz, selection_sort);
    }
    if( array_size >= 64 ) // O(n lg n) (average case for quick sort)
    {
        execute_sort_test("Merge Sort", &viz, merge_sort);

        execute_sort_test("Heap Sort", &viz, heap_sort);

        execute_sort_test(
            "Lomuto Quick Sort (Default Pivot)", &viz, lomuto_quick_sort);

        execute_sort_test(
            "Lomuto Quick Sort (Random Pivot)", &viz, lomuto_random_quick_sort);

        execute_sort_test("Lomuto Quick Sort (Median-of-Three Pivot)",
                          &viz,
                          lomuto_random_quick_sort);

        execute_sort_test(
            "Hoare Quick Sort (Default Pivot)", &viz, hoare_quick_sort);

        execute_sort_test(
            "Hoare Quick Sort (Random Pivot)", &viz, hoare_random_quick_sort);

        execute_sort_test("Hoare Quick Sort (Median-of-Three Pivot)",
                          &viz,
                          hoare_random_quick_sort);

        execute_sort_test("Intro Sort", &viz, intro_sort);
    }

    if( array_size <= 30 ) // Impractical sorts
    {
        execute_sort_test("Bogo Sort", &viz, bogo_sort);
        execute_sort_test("Slow Sort", &viz, slow_sort);
    }

    printf("Finished testing sorting of %d ", array_size);

    if( random )
    {
        printf("randomized");
    }
    else
    {
        printf("reversed");
    }
    printf(" elements.\n\n");

    clean_up(&viz);

    return 0;
}

void create_arrays(visualizer_t *viz)
{
    viz->array = ( int * )malloc(viz->array_size * sizeof(int));
    viz->original_array = ( int * )malloc(viz->array_size * sizeof(int));
    viz->sorted_array = ( int * )malloc(viz->array_size * sizeof(int));

    for( int i = 0; i < viz->array_size; i++ )
    {
        if( !viz->sorted )
        {
            viz->array[i] = viz->array_size - i;
        }
        else
        {
            viz->array[i] = i + 1;
        }
        viz->sorted_array[i] = i + 1;
    }

    if( viz->random )
    {
        srand(time(NULL));
        shuffle_array(viz);
    }

    memcpy(viz->original_array, viz->array, viz->array_size * sizeof(int));
}

void alg_file_name(char *alg, char *file_name)
{
    unsigned long j = 0;
    for( unsigned long i = 0; i < strlen(alg); ++i, ++j )
    {
        if( alg[i] >= 'a' && alg[i] <= 'z' )
        {
            file_name[j] = alg[i];
        }
        else if( alg[i] >= 'A' && alg[i] <= 'Z' )
        {
            file_name[j] = alg[i] + ('a' - 'A');
        }
        else if( alg[i] == ' ' )
        {
            file_name[j] = '_';
        }
        else
        {
            --j;
        }
    }

    file_name[j] = '\0';
}

void execute_sort_test(char *alg,
                       visualizer_t *viz,
                       void (*sorter)(visualizer_t *))
{
    strcpy(viz->alg, alg);
    viz->ffmpeg = (viz->video) ? popen(viz->ffmpeg_command, "w") : NULL;

    if( !viz->ffmpeg && viz->video )
    {
        handle_error(
            FFMPEG_ERROR, viz->renderer, viz->window, nullptr, nullptr);
    }

    viz->comparisons = 0;
    viz->accesses = 0;
    viz->swaps = 0;
    viz->number_sorted = 0;
    viz->recursion_level = viz->recursion_limit = -1;
    inversion_count(viz);
    viz->original_inversions = viz->inversions;

    draw_array(viz);

    sorter(viz);

    draw_array(viz);

    char file_name[64];
    alg_file_name(viz->alg, file_name);

    print_results(file_name, viz);

    memcpy(viz->array, viz->original_array, viz->array_size * sizeof(int));

    rename_video(file_name, viz);

    SDL_SetRenderDrawColor(viz->renderer, 0, 0, 0, 255);
    SDL_RenderClear(viz->renderer);
}

void print_results(char *file_name, visualizer_t *viz)
{
    if( viz->video )
    {
        fflush(viz->ffmpeg);
        pclose(viz->ffmpeg);
        printf(" Video saved as %s.mov", file_name);
    }
    printf("\n");

    if( !viz->print )
    {
        return;
    }

    mkdir("./results", 0777);

    char results_file_name[64];
    snprintf(results_file_name,
             sizeof(results_file_name),
             "results/%s_%s_%d.txt",
             file_name,
             lower_order_title(viz),
             viz->array_size);

    FILE *results_file = fopen(results_file_name, "w");
    fprintf(results_file,
            "Algorithm: %s - %s Order\n"
            "Array Size: %d\n"
            "Original Inversion Count: %d\n"
            "Comparisons: %d\n"
            "Array Accesses: %d\n"
            "Swaps: %d",
            viz->alg,
            order_title(viz),
            viz->array_size,
            viz->original_inversions,
            viz->comparisons,
            viz->accesses,
            viz->swaps);

    fflush(results_file);
    fclose(results_file);
}

void rename_video(char *file_name, visualizer_t *viz)
{
    if( !viz->video )
    {
        return;
    }

    char output_video_name[32];
    snprintf(output_video_name, sizeof(output_video_name), "%s.mov", file_name);

    rename("video.mov", output_video_name);
}

void clean_up(visualizer_t *viz)
{
    free(viz->array);
    free(viz->original_array);
    free(viz->pixels);
    TTF_CloseFont(viz->font);
    SDL_DestroyRenderer(viz->renderer);
    SDL_DestroyWindow(viz->window);
    TTF_Quit();
    SDL_Quit();
}