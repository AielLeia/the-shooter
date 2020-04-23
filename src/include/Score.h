#ifndef _SCORE_H_
#define _SCORE_H_

#include "Common.h"

struct _Score {
    int     currentScore;
    int     higherScore;
    Entity  e;
};

extern Score load_Score();
extern void destroy_Score( Score *s );

extern void blit_Score( Score *s, SDL_Renderer *renderer );

#endif