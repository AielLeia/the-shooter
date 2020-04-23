#include "Common.h"

static Explosion *load_Explosion( Enemy *e, SDL_Renderer *renderer );
static void destroy_Explosion( Explosion *e );

static Debris *load_Debrit( Enemy *e );
static void destroy_Debrit( Debris *d );

ListExplosion load_ListExplosion() {
    ListExplosion list;
    list.first = NULL;
    list.last = NULL;
    return list;
}

ListDebris load_ListDebris()  {
    ListDebris list;
    list.first = NULL;
    list.last = NULL;
    return list;
}

void add_Explosion( ListExplosion *list, Enemy *e, SDL_Renderer *renderer ) {
    Explosion *explosion = load_Explosion( e, renderer );
    if (list->first == NULL && list->last == NULL)
        list->first = list->last = explosion;
    else {
        explosion->prev = list->last;
        list->last->next = explosion;
        list->last = explosion;
    }
}

void destroy_ListExplosion( ListExplosion *list ) {
    if (list->first == NULL && list->last == NULL) return;
    for (Explosion *e = list->first; e != NULL; e = e->next) destroy_Explosion( e );
    list->first = list->last = NULL;
}

void add_Debris( ListDebris *list, Enemy *e ) {
}

void blit_Explosion( ListExplosion *listExplosion, SDL_Renderer *renderer ) {
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_ADD);
    for (Explosion *ex = listExplosion->first; ex != NULL; ex = ex->next) {
        if (ex->life-- == 0) {
            if (ex == listExplosion->first && ex == listExplosion->last) {
                destroy_Explosion( ex );
                listExplosion->first = listExplosion->last = NULL;
                break;
            } else if (ex->prev == NULL) {
                listExplosion->first = listExplosion->first->next;
                listExplosion->first->prev = NULL;
                ex->next = NULL;
                destroy_Explosion( ex );
                continue;
            } else if (ex->next == NULL) {
                listExplosion->last = listExplosion->last->prev;
                listExplosion->last->next = NULL;
                ex->prev = NULL;
                destroy_Explosion( ex );
                continue;
            } else if (ex->next != NULL && ex->prev != NULL) {
                ex->prev->next = ex->next;
                ex->next->prev = ex->prev;
                ex->next = ex->prev = NULL;
                destroy_Explosion( ex );
                continue;
            }
        }
	    SDL_SetTextureBlendMode(ex->e.texture, SDL_BLENDMODE_ADD);
        SDL_SetTextureColorMod(ex->e.texture, ex->color.r, ex->color.g, ex->color.b);
		SDL_SetTextureAlphaMod(ex->e.texture, ex->color.a);

        SDL_Rect dest;
        dest.x = ex->e.p.x;
        dest.y = ex->e.p.y;
        SDL_QueryTexture(ex->e.texture, NULL, NULL, &dest.w, &dest.h);
        SDL_RenderCopy(renderer, ex->e.texture, NULL, &dest);
    }
}

void blit_Debrit( ListDebris *listDebris, SDL_Renderer *renderer ) {

}

static Explosion *load_Explosion( Enemy *e, SDL_Renderer *renderer ) {
    const int FPS = 60;
    Explosion *explosion = (Explosion *)malloc( sizeof(Explosion) );
    explosion->e.texture = IMG_LoadTexture( renderer, "assets/explosion.png" );
    explosion->e.p.x = e->p.e.p.x - (e->p.e.p.w / 2);
    explosion->e.p.y = e->p.e.p.y;
    explosion->e.p.w = 96;
    explosion->e.p.h = 96;
    explosion->life = 15;
    explosion->next = explosion->prev = NULL;

    switch (rand() % 4)
    {
        case 0:
            explosion->color.r = 255;
            explosion->color.g = 0;
            explosion->color.b = 0;
            break;
            
        case 1:
            explosion->color.r = 255;
            explosion->color.g = 128;
            explosion->color.b = 0;
            break;
            
        case 2:
            explosion->color.r = 255;
            explosion->color.g = 255;
            explosion->color.b = 0;
            break;
            
        default:
            explosion->color.r = 255;
            explosion->color.g = 255;
            explosion->color.b = 255;
            break;
    }
    explosion->color.a = rand() % FPS * 3;
    return explosion;
}

void destroy_Explosion( Explosion *e ) {
    SDL_DestroyTexture( e->e.texture );
    free( e );
    e = NULL;
}