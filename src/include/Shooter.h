#ifndef _SHOOTER_H_
#define _SHOOTER_H_

#include "Common.h"

enum _AppState {
    RUNNING, STOP, RELOAD
};

struct _BackgroundStart {
    float x;
    float y;
    float speed;
};

struct _AppBackground {
    SDL_Texture         *texture;
    BackgroundStart     starts[MAX_STARS];
};

struct _App {
    SDL_Window      *window;
    SDL_Renderer    *renderer;
    AppBackground   background;
    AppState        state;
};

extern void init_App     ( App *app );
extern void destroy_App  ( App *app );

extern void update_App( App *app );
extern void blit_App( App *app );

#endif