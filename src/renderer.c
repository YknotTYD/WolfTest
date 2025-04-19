//renderer.c

#include "../include/main.h"
#include "../include/sally.h"
#include "../include/sky.h"

/*static long double min(long double a, long double b)
{
    if (a < b) {
        return a;
    }
    return b;
}

static int delta_cmp(long double n, long double delta)
{
    if (delta > 0) {
        return n >= 0 && n <= delta;
    }
    return n <= 0 && n >= delta;
}

static void load_intersect(
    long double intersect[2],
    long double x1, long double y1, long double x2, long double y2,
    long double x3, long double y3, long double x4, long double y4
) {
    long double a = x2 - x1;
    long double b = x4 - x3;
    long double c = x3 - x1;
    long double d = y2 - y1;
    long double e = y4 - y3;
    long double f = y3 - y1;

    long double delta = (a * e - d * b);
    long double s;
    long double t;

    intersect[0] = 0.0/0.0;
    intersect[1] = 0.0/0.0;

    s = (c * e - f * b);
    if (!delta_cmp(s, delta)){
        return;
    }

    t = (c * d - f * a);
    if (!delta_cmp(t, delta)){
        return;
    }

    intersect[0] = x1 + (s / delta) * a;
    intersect[1] = y1 + (s / delta) * d;

    return;
}

static void process_ray(
    context_t *context, long double norm,
    int ray_index, long double ray_angle,
    long double intersect[2], line_t *line
) {
    //long double vect[2] = {line->points[0] - intersect[0], line->points[1] - intersect[1]};
    //long double relnorm = sqrt(SQUARE(vect[0]) + SQUARE(vect[1]));
    //sprite_t *sprite = &context->sprites[line->index];
    int height;

    (void)min;
    (void)intersect;
    (void)line;
    norm *= cos(context->player->angle - ray_angle);
    height = WALLHEIGHT / norm;

    SDL_SetRenderDrawColor(context->ren, 255, 0, 0, 255);
    for (int i = context->screen_size[1] / 2- height / 2; i < context->screen_size[1] / 2 + height / 2; i++) {
        SDL_RenderDrawPoint(context->ren, ray_index, i);
    }

    return;
}
*/
void launch_ray(
    context_t *context, long double ray[4],
    long double mintersect[2], long double *normin, line_t **minline
) {
    (void)context;
    (void)ray;
    (void)mintersect;
    (void)normin;
    (void)minline;
   /* long double intersect[2];
    long double norm = 0;
    int norminindex = -1;

    mintersect[0] = 0.0 / 0.0;
    mintersect[1] = 0.0 / 0.0;
    *normin = 1.0 / 0.0;

    for (int i = 0; i < context->line_count; i++) {
        load_intersect(
            intersect,
            UNPACK4(ray),
            UNPACK4(context->lines[i].points)
        );
        if (intersect[0] != intersect[0]) {
            continue;
        }
        norm = SQUARE(intersect[0] - ray[0]) + SQUARE(intersect[1] - ray[1]);
        if (norm >= *normin) {
            continue;
        }
        *normin = norm;
        norminindex = i;
        mintersect[0] = intersect[0];
        mintersect[1] = intersect[1];
    }

    if (norminindex == -1) {
        return;
    }

    *normin = sqrt(*normin);    *minline = &context->lines[norminindex];
    *minline = &context->lines[norminindex];
*/
    return;
}

void render_walls(context_t *context)
{
    player_t *player = context->player;
    float angle;
    float ray[6];
    float n;
    float x;
    float y;
    float ray_zangle;

    (void)ray;
    /*long double intersect[2];
    long double norm;
    line_t *line;*/

    /*r (int y = 0; y < context->screen_size[1]; y++) {
        for (int x = 0; x < context->screen_size[0]; x++) {
            if (rand() % 2) {//y % (context->screen_size[1] / 10) > 10) {
                SDL_SetRenderDrawColor(context->ren, 255, 255, 255, 255);
                //printf("s");
            } else {
                SDL_SetRenderDrawColor(context->ren, 0, 0, 0, 255);
                //printf("d");
            }
            SDL_RenderDrawPoint(context->ren, x, y);
            //printf("p");
        }
    }
    return;*/

    long double half_fov = DEG_TO_RAD(PLAYER_HFOV) / 2.0;
    //long double plane;
    float norm;
    player->angle += 3 * PI / 4.0;
    char color[3];

    //add FOW
    for (int ray_index = 0; ray_index < player->ray_count; ray_index++) {

        for (int ray_z = context->screen_size[1] / 2; ray_z < context->screen_size[1]; ray_z++) {


        //plane = (2.0 * ray_z / (context->screen_size[1] + 1)) - 1.0;
        //ray_zangle = atan(plane * tan(half_fov));
        ray_zangle = atan((2.0 * (ray_z - context->screen_size[1]/2 * 1) / context->screen_size[1]) * tan(half_fov));
        //ray_zangle = context->screen_size[1] - (ray_z - context->screen_size[1] * 0) * 0.01;



        //angle = player->angle + player->angles[ray_index];
        angle = player->angle + (ray_index / (float)player->ray_count * DEG_TO_RAD(player->FOV));

        ray[0] = player->pos[0];
        ray[1] = player->pos[1];
        ray[2] = PLAYER_Z;
        ray[3] = cos(angle) * cos(player->head_angle + ray_zangle);
        ray[4] = sin(angle) * cos(player->head_angle + ray_zangle);
        ray[5] = sin(player->head_angle + ray_zangle);

        /*{bx + rx * n;
         by + ry * n;
         bz + rz * n}

        n = (FLOOR_Z - bz) / rz;*/
        n = (FLOOR_Z - ray[2]) / ray[5];
        x = ray[0] + ray[3] * n;
        y = ray[1] + ray[4] * n;

        /*if ((int)((int)(x/FLOOR_TILE_SIZE) + (int)(y/FLOOR_TILE_SIZE)) % 2) {
            SDL_SetRenderDrawColor(context->ren, 255, 0, 0,  255);
        } else {
            SDL_SetRenderDrawColor(context->ren, 0, 0, 255,  255);
        }*/

        (void)norm;
        //norm = sqrt(((x - player->pos[0]) * (x - player->pos[0])) + ((y - player->pos[1]) + (y - player->pos[1])));
        x = ABS(fmod(x, FLOOR_TILE_SIZE));
        y = ABS(fmod(y, FLOOR_TILE_SIZE));
        x /= FLOOR_TILE_SIZE;
        y /= FLOOR_TILE_SIZE;
        x *= SALLY_WIDTH;
        y *= SALLY_HEIGHT;

        /*if (x >= SALLY_WIDTH || y >= SALLY_HEIGHT || y < 0 || x < 0) {
            printf("%i %i %i %i\n", SALLY_WIDTH, (int)x, SALLY_HEIGHT, (int)y);
            exit(69);
        }*/

        color[0] = sally[(int)y][(int)x][0];
        color[1] = sally[(int)y][(int)x][1];
        color[2] = sally[(int)y][(int)x][2];

        /*if (norm > 1000) {
            norm = norm - 1000;
            norm = norm > 1000 ? 1000 : norm;
            norm /= 1000.0;
            color[0] = (color[0] * 2 * (1 - norm) + 255 * 2 * norm) / 2;
            color[1] = (color[1] * 2 * (1 - norm) + 255 * 2 * norm) / 2;
            color[2] = (color[2] * 2 * (1 - norm) + 255 * 2 * norm) / 2;
        }*/

        SDL_SetRenderDrawColor(context->ren, color[0], color[1], color[2],  255);

        SDL_RenderDrawPoint(context->ren, ray_index, ray_z);
        }
    }

      for (int ray_index = 0; ray_index < player->ray_count; ray_index++) {

        for (int ray_z = 0; ray_z < context->screen_size[1] / 2; ray_z++) {

        ray_zangle = atan((2.0 * (ray_z - context->screen_size[1]/2 * 1) / context->screen_size[1]) * tan(half_fov));
        angle = player->angle + (ray_index / (float)player->ray_count * DEG_TO_RAD(player->FOV));

        ray[3] = cos(angle) * cos(player->head_angle + ray_zangle);
        ray[4] = sin(angle) * cos(player->head_angle + ray_zangle);
        ray[5] = sin(player->head_angle + ray_zangle);

        n = 300 / ray[5];
        x = ray[3] * n;
        y = ray[4] * n;

        x = ABS(fmod(x, SKY_WIDTH));
        y = ABS(fmod(y, SKY_HEIGHT));

        color[0] = sky[(int)y][(int)x][0];
        color[1] = sky[(int)y][(int)x][1];
        color[2] = sky[(int)y][(int)x][2];

        SDL_SetRenderDrawColor(context->ren, color[0], color[1], color[2],  255);

        SDL_RenderDrawPoint(context->ren, ray_index, ray_z);
        }

    }
    player->angle -= 3 * PI / 4.0;
    return;
}
