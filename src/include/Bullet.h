#ifndef _BULLET_H_
#define _BULLET_H_

#include "Common.h" 


struct _BulletDelegate {
    void (*blit_Bullet)( Bullet *, SDL_Renderer * );
};

struct _ListBullet {
    Bullet *first;
    Bullet *last;
};

struct _Bullet {
    float           speed;
    bool            isVisible; 
    Entity          e;
    BulletDelegate  method;
    struct _Bullet  *next;
    struct _Bullet  *prev;
};

extern Bullet* load_Bullet( SDL_Renderer *renderer, const char *textureName, const float x, const float y, const float w, const float h );
extern void destroy_Bullets( ListBullet *bullets ); 
extern void destroy_Bullet( Bullet *bullet );

extern void blit_Bullet( Bullet *bullet, SDL_Renderer *renderer );
extern void update_Bullet( ListBullet *allBullet, bool (*condition)(Bullet *), void (*callback)( Bullet *) );

#endif