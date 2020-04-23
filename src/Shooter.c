#include "Common.h"

static long long int backgroundX = 0;

static void init_Background( App *app );

void update_App( App *app ) {
    if (--backgroundX < -SCREEN_W)
	{
		backgroundX = 0;
	}

    for (int i = 0 ; i < MAX_STARS ; i++)
	{
		app->background.starts[i].x -= app->background.starts[i].speed;
		
		if (app->background.starts[i].x < 0)
		{
			app->background.starts[i].x = SCREEN_W + app->background.starts[i].x;
		}
	}
}

void blit_App( App *app ) {
    SDL_Rect dest;    
    for (int x = backgroundX ; x < SCREEN_W ; x += SCREEN_W)
	{
		dest.x = x;
		dest.y = 0;
		dest.w = SCREEN_W;
		dest.h = SCREEN_H;
		
		SDL_RenderCopy(app->renderer, app->background.texture, NULL, &dest);
	}

	SDL_RenderCopy(app->renderer, app->background.texture, NULL, &dest);
    for (int i = 0; i < MAX_STARS; i++) {
        int c = 32 * app->background.starts[i].speed;
		SDL_SetRenderDrawColor(app->renderer, c, c, c, 255);
        SDL_SetRenderDrawColor( app->renderer, 255, 255, 255, 255);
        SDL_RenderDrawPoint( app->renderer, app->background.starts[i].x, app->background.starts[i].y);
    }
}

void init_App( App *app ) {
    app->state = RUNNING;
    app->window = SDL_CreateWindow(
        "Shooter",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        SCREEN_W, SCREEN_H,
        SDL_WINDOW_SHOWN
    );

    app->renderer = SDL_CreateRenderer(
        app->window,
        -1,
        SDL_RENDERER_ACCELERATED
    );

    init_Background( app );
}

void destroy_App( App *app ) {
    SDL_DestroyRenderer( app->renderer );
    SDL_DestroyWindow( app->window );
}

static void init_Background( App *app ) {
    app->background.texture = IMG_LoadTexture( app->renderer, "assets/background.png" );
    for (int i = 0 ; i < MAX_STARS ; i++) {
        app->background.starts[i].x     = rand() % SCREEN_W;
		app->background.starts[i].y     = rand() % SCREEN_H;
		app->background.starts[i].speed = 1 + rand() % 8;
	}
}