#ifndef _ENTITY_H_
#define _ENTITY_H_

#include "Common.h"

struct _Properties {
    float   x;
    float   y;
    float   w;
    float   h;
};

struct _Entity {
    Properties      p;
    SDL_Texture     *texture;
};

#endif 