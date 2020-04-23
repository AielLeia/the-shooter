#include "Common.h"

Bullet *load_Bullet( SDL_Renderer *renderer, const char *textureName, const float x, const float y, const float w, const float h ) {
    Bullet *b = (Bullet *)malloc( sizeof(Bullet) );

    b->e.p.x = x;
    b->e.p.y = y;
    b->e.p.w = w;
    b->e.p.h = h;
    b->e.texture = IMG_LoadTexture( renderer, textureName );
    b->speed = 10.0f;
    b->isVisible = true;
    b->next = NULL;
    b->prev = NULL;
    
    // Bind
    b->method.blit_Bullet = blit_Bullet;

    return b;
}

void destroy_Bullets( ListBullet *bullets ) {
    if (bullets->first == NULL && bullets->last == NULL) return;
    for (Bullet *b = bullets->first; b != NULL; b = b->next) destroy_Bullet( b );
    bullets->first = bullets->last = NULL;
}

void destroy_Bullet( Bullet *bullet ) {
    SDL_DestroyTexture( bullet->e.texture );
    free( bullet );
    bullet = NULL;
}

void blit_Bullet( Bullet *bullet, SDL_Renderer *renderer ) {
    SDL_Rect dest;
	dest.x = bullet->e.p.x;
	dest.y = bullet->e.p.y;
	SDL_QueryTexture(bullet->e.texture, NULL, NULL, &dest.w, &dest.h);
	SDL_RenderCopy(renderer, bullet->e.texture, NULL, &dest);
}

void update_Bullet( ListBullet *allBullet, bool (*condition)(Bullet *), void (*callback)( Bullet *) ) {
    for (Bullet *f = allBullet->first; f != NULL; f = f->next) {
        if (condition( f )) {
            if (f == allBullet->first && f == allBullet->last) {
                destroy_Bullet( f );
                allBullet->first = allBullet->last = NULL;
                break;
            }
            allBullet->last = f->prev;
            f->prev->next = NULL;
            f->prev = NULL;
            destroy_Bullet( f );
            break;
        }
        callback( f );
    }
}