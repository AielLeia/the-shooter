#include "Common.h"

static void capFrameRate(long *then, float *remainder)
{
	long wait, frameTime;
	wait = 16 + *remainder;
	*remainder -= (int)*remainder;
	frameTime = SDL_GetTicks() - *then;
	wait -= frameTime;
	if (wait < 1) wait = 1;
	SDL_Delay(wait);
	*remainder += 0.667;
	*then = SDL_GetTicks();
}

int main ( int argc, char *argv[] ) {
    TTF_Init();
    SDL_Init( SDL_INIT_VIDEO );
    IMG_Init( IMG_INIT_PNG );
 
    App app;
    init_App( &app );

    long then;
	float remainder;

    Player p;
    load_Player( 
        &p, 
        app.renderer, 
        "assets/player.png",
        100, 100,
        48, 46
    );

    ListEnemies listEnemy = load_ListEnemies();
    ListExplosion listExplosion = load_ListExplosion();

    then = SDL_GetTicks();
    remainder =  0;

    SDL_Event e;
    while (app.state == RUNNING) {
        while (SDL_PollEvent( &e )) {
            if (e.type == SDL_QUIT) app.state = STOP;
            if (e.type == SDL_KEYDOWN) p.method.event_Handler( &p, SDL_GetKeyboardState( NULL ), app.renderer );
        }

        update_App( &app );
        p.method.update_Player( &p );
        update_ListEnemies( &listEnemy, &p, &listExplosion, &app, app.renderer );
        if (app.state == RELOAD) {
            app.state = RUNNING;
            destroy_ListExplosion( &listExplosion );
            destroy_ListEnemies( &listEnemy );
            destroy_Player( &p );
            load_Player( 
                &p, 
                app.renderer, 
                "assets/player.png",
                100, 100,
                48, 46
            );
            listExplosion = load_ListExplosion();
            listEnemy = load_ListEnemies();
            continue;
        }

        SDL_SetRenderDrawColor( app.renderer, 53, 53, 53, 255 );
        SDL_RenderClear( app.renderer );
        blit_App( &app );
        p.method.blit_Player( &p, app.renderer );
        blit_Explosion( &listExplosion, app.renderer );
        blit_ListEnemies( &listEnemy, app.renderer );
        SDL_RenderPresent( app.renderer );
        capFrameRate( &then, &remainder );
    }
    
    destroy_ListExplosion( &listExplosion );
    destroy_ListEnemies( &listEnemy );
    destroy_Player( &p );
    destroy_App( &app );
    IMG_Quit();
    SDL_Quit();
    return EXIT_SUCCESS;
}