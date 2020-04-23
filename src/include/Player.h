#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "Common.h"  

struct _PlayerDelegate {
    void (*blit_Player)(Player *, SDL_Renderer *);
    void (*event_Handler)(Player *, const Uint8 *, SDL_Renderer*);
    void (*update_Player)(Player *);
};

struct _Player {
    Entity          e;
    ListBullet      bullet;
    PlayerDelegate  method;
};

extern void load_Player( Player *player, SDL_Renderer *renderer, const char *textureName, const float x, const float y, const float w, const float h  );
extern void destroy_Player( Player *player );


extern void blit_Player( Player *player, SDL_Renderer *renderer );
extern void event_Handler( Player *player, const Uint8 *keyState, SDL_Renderer *renderer );
extern void update_Player( Player *player );

#endif