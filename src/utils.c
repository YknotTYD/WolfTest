//utils.c

#include "../include/main.h"

void init_context(context_t *context, int screen_size[2])
{
    sprite_t *sky = malloc(sizeof(sprite_t));
    sprite_t *night = malloc(sizeof(sprite_t));

    TTF_Init();
    IMG_Init(IMG_INIT_PNG);
    context->font = TTF_OpenFont("assets/fonts/SourceCodePro-Medium.ttf", 60 / SCALE);
    context->sky = sky;
    context->night = night;

    
    context->win = SDL_CreateWindow("Mood-2", 100, 75, screen_size[0] * SCALE, screen_size[1] * SCALE, SDL_WINDOW_SHOWN);
    context->ren = SDL_CreateRenderer(context->win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    SDL_RenderSetScale(context->ren, SCALE, SCALE);
    context->quit = 0;

    context->sky->texture = IMG_LoadTexture(context->ren, "assets/sky_.jpg");
    context->night->texture = IMG_LoadTexture(context->ren, "assets/milk.jpg");
    SDL_QueryTexture(context->sky->texture, 0, 0, &context->sky->width, &context->sky->height);
    SDL_QueryTexture(context->night->texture, 0, 0, &context->night->width, &context->night->height);
    SDL_SetTextureBlendMode(context->sky->texture, SDL_BLENDMODE_BLEND);
    SDL_SetTextureBlendMode(context->night->texture, SDL_BLENDMODE_BLEND);

    if (context->sky->texture == 0 || context->night->texture == 0) {
        printf("%s\n", SDL_GetError());
        exit(69);
    }
    context->screen_size[0] = screen_size[0];
    context->screen_size[1] = screen_size[1];
    SDL_SetRenderDrawBlendMode(context->ren, SDL_BLENDMODE_BLEND);
    SDL_ShowCursor(SDL_DISABLE);

    context->line_count = 1;
    context->lines = malloc(sizeof(line_t) * 1);

    context->lines[0].index = 0;
    context->lines[0].points[0] = 0;
    context->lines[0].points[1] = 0;
    context->lines[0].points[2] = 100;
    context->lines[0].points[3] = 100;

    return;
}

void update_fps(context_t *context, long double frame_fps)
{
    long double temp;

    for (int i = 0; i < FPS - 1; i++) {
        temp = context->frames[i];
        context->frames[i] = context->frames[i + 1];
        context->frames[i + 1] = temp;
    }
    context->frames[FPS - 1] = frame_fps;
    return;
}

static char *int_to_str(int nbr)
{
    int start = 0;
    int end;
    char *str = malloc(64);
    char temp;
    int i = 0;

    do {
        str[i] = '0' + (nbr % 10);
        i++;
        nbr /= 10;
    } while (nbr);
    str[i] = '\0';
    end = i - 1;
    while (start < end) {
        temp = str[start];
        str[start] = str[end];
        str[end] = temp;
        start++;
        end--;
    }
    return str;
}


static char *get_fpsstr(context_t *context)
{
    char *fpsstr;
    double fps = 0;

    for (int i = 0; i < FPS; i++) {
        fps += context->frames[i];
    }
    fps /= FPS;

    //printf("%f\n", fps);
    fpsstr = int_to_str(fps);
    return fpsstr;
}

void display_fps(context_t *context)
{
    int width;
    int height;
    char *fpsstr = get_fpsstr(context);

    //return;    
    (void)fpsstr;
    SDL_Surface *surf = TTF_RenderText_Blended_Wrapped(context->font, fpsstr,
        (SDL_Color){255, 255, 255, 255}, context->screen_size[0] - 10);
    SDL_Texture *text = SDL_CreateTextureFromSurface(context->ren, surf);
    SDL_QueryTexture(text, 0, 0, &width, &height);

    SDL_RenderCopy(
        context->ren, text, 0,
        &(SDL_Rect){
        10, 10,
        width, height}
    );

    SDL_FreeSurface(surf);
    SDL_DestroyTexture(text);

    return;
}

void update_vel(context_t *context)
{
    SDL_GetMouseState(&context->mouse_pos[0], &context->mouse_pos[1]);

    context->vel[0] = context->mouse_pos[0] - context->screen_size[0] / 2;
    context->vel[1] = context->mouse_pos[1] - context->screen_size[1] / 2;

    context->player->head_angle += context->vel[1] * 5e-3;
    context->player->head_angle = fmod(context->player->head_angle, PI * 2);
    context->player->head_angle = MIN(context->player->head_angle, 1);
    context->player->head_angle = MAX(context->player->head_angle, -1);

    /*if ((SDL_GetWindowFlags(context->win) & SDL_WINDOW_MOUSE_FOCUS) == 0 ||
        SDL_GetMouseFocus() != context->win) {
        return;
    }*/

    SDL_WarpMouseInWindow(
        context->win,
        context->screen_size[0] / 2,
        context->screen_size[1] / 2
    );

    return;
}
