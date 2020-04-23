#ifndef _EFFECT_H_
#define _EFFECT_H_

#include "Common.h"

struct _Explosion {
    Entity              e;
    float               life;
    SDL_Color           color;
    struct _Explosion   *next;
    struct _Explosion   *prev;
};

struct _ListExplosion {
    Explosion *first;
    Explosion *last;
};

struct _Debris {
    Entity          e;
    float           life;
    SDL_Rect        rect;
    struct _Debris  *next;
    struct _Debris  *prev;
};

struct _ListDebris {
    Debris  *first;
    Debris  *last;
};

extern ListExplosion load_ListExplosion();
extern ListDebris load_ListDebris();

extern void destroy_ListExplosion( ListExplosion *list );
extern void destroy_ListDebris( ListDebris *list );

extern void add_Explosion( ListExplosion *list, Enemy *e, SDL_Renderer *renderer );
extern void add_Debris( ListDebris *list, Enemy *e );

extern void blit_Explosion( ListExplosion *listExplosion, SDL_Renderer *renderer );
extern void blit_Debrit( ListDebris *listDebris, SDL_Renderer *renderer );


#endif