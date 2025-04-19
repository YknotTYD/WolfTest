//main.h

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <math.h>

#ifndef MAIN_HEADER

    #define MAIN_HEADER
    #define UNPACK2(arr) arr[0], arr[1]
    #define UNPACK4(arr) (arr)[0], (arr)[1], (arr)[2], (arr)[3]
    #define NOW (clock()/(double)CLOCKS_PER_SEC)
    #define PI 3.1415926535897932384626433832795028841L
    #define DEG_TO_RAD(angle) (((angle) / 180.0) * PI)
    #define ABS(n) ((n) > 0 ? (n): -(n))
    #define SQUARE(n) ((n) * (n))
    #define SHIFT_ALPHA 0
    #define SHIFT_BLUE 8
    #define SHIFT_GREEN 16
    #define SHIFT_RED 24
    #define GRADIENT(n, d, shift) ((unsigned int)(0xFF * ((n) / (double)(d))) << (shift));
    #define INVERSE_GRADIENT(n, d, shift) ((255 - ((unsigned int)(0xFF * ((n) / (double)(d))))) << (shift));
    #define PLAYER_RADIUS 10
    #define PLAYER_SPEED 7
    #define PLAYER_ANGULAR_SPEED 0.005
    #define RAY_LEN 1e+9
    #define WALLHEIGHT 31000
    #define FPS 120
    #define RENDER_NORMULT 10
    #define PLAYER_STEP_SPEED 50
    #define PLAYER_STEP_HEIGHT 7
    #define MODE7_SCALE_FACT 2
    #define SCALE 3.0

    #define PLAYER_Z 50
    #define PLAYER_HFOV 90
    #define FLOOR_Z 5
    #define FLOOR_TILE_SIZE 50.0

typedef struct {
    long double pos[2];
    long double angle;
    long double z; 
    long double *angles;
    long double ray_step;
    int FOV;
    float head_angle;
    int ray_count;
} player_t;

typedef struct {
    int points[4];
    int index;
} line_t;

typedef struct {
    int width;
    int height;
    SDL_Texture *texture;
} sprite_t;

typedef struct {
    SDL_Window *win;
    SDL_Renderer *ren;
    SDL_Event events;
    player_t *player;
    TTF_Font *font;
    line_t *lines;
    sprite_t *sprites;
    sprite_t *sky;
    sprite_t *night;
    SDL_Surface *floor;
    int floor_width;
    int floor_height;
    int line_count;
    int sprite_count;
    int quit;
    int screen_size[2];
    int mouse_pos[2];
    int vel[2];
    long double frames[FPS];
} context_t;

typedef unsigned int color_t;

void init_context(context_t *context,int screen_size[2]);
void update_fps(context_t *context, long double frame_fps);
void display_fps(context_t *context);

void init_player(player_t **player, int ray_count);
void render_player(context_t *context);
void render_lines(context_t *context);
void update_player(context_t *context, long double clock);
void update_vel(context_t *context);

void launch_ray(context_t *context, long double ray[4], long double mintersect[2], long double *normin, line_t **minline);
void render_walls(context_t *context);
void render_floor(context_t *context);

#endif
