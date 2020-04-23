#ifndef _ENEMIE_H_
#define _ENEMIE_H_

#include "Common.h"

struct _Enemy {
    Player          p;
    float           speedX;
    float           speedY;
    struct _Enemy   *next;
    struct _Enemy   *prev;
};
 
struct _ListEnemies {
    Enemy  *first;
    Enemy  *last;
};

extern ListEnemies load_ListEnemies();
extern void destroy_ListEnemies( ListEnemies *list );
extern void destroy_Enemy( Enemy *enemy );

extern void update_ListEnemies( ListEnemies *list, Player *player, ListExplosion *listExplosion, App *app, SDL_Renderer *renderer );
extern void blit_ListEnemies( ListEnemies *list, SDL_Renderer *renderer );

#endif