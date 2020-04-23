#include "Common.h"

extern long long int scoreValue;

static long long int enemyAppearance    = 150;
static long long int shootingTimer      = 350;

static void appearance( ListEnemies *list, SDL_Renderer *renderer );
static void  add_Enemy( ListEnemies *list, Enemy *enemy );

static Enemy *load_Enemy( SDL_Renderer *renderer );
static bool update_Enemy( Enemy *e, Player *p, App *app, SDL_Renderer *renderer );
static void fire( Enemy *e, SDL_Renderer *renderer );
static void callback( Bullet *bullet );
static bool condition( Bullet *bullet );

static bool hit_Bullet( Enemy *e, ListBullet *list );

ListEnemies load_ListEnemies() {
    scoreValue = 0;
    ListEnemies list;
    list.first = NULL;
    list.last = NULL;
    return list;
}

void destroy_ListEnemies( ListEnemies *list ) {
    if (list->first == NULL && list->last == NULL) return;
    for (Enemy *e = list->first; e != NULL; e = e->next) destroy_Enemy( e );
    list->first = list->last = NULL;
}

void blit_ListEnemies( ListEnemies *list, SDL_Renderer *renderer ) {
    for (Enemy *e = list->first; e != NULL; e = e->next) {
        e->p.method.blit_Player( &e->p, renderer );
    }
}

void update_ListEnemies( ListEnemies *list, Player *player, ListExplosion *listExplosion, App *app, SDL_Renderer *renderer ) {
    for (Enemy *e = list->first; e != NULL; e = e->next) {
        if (e->p.e.p.x <= -e->p.e.p.w || hit_Bullet( e, &player->bullet )) {
            add_Explosion(listExplosion, e, renderer);
            if (e == list->first && e == list->last) {
                destroy_Enemy( e );
                list->first = list->last = NULL;
                break;
            } else if (e->prev == NULL) {
                list->first = list->first->next;
                list->first->prev = NULL;
                e->next = NULL;
                destroy_Enemy( e );
                continue;
            } else if (e->next == NULL) {
                list->last = list->last->prev;
                list->last->next = NULL;
                e->prev = NULL;
                destroy_Enemy( e );
                continue;
            } else if (e->next != NULL && e->prev != NULL) {
                e->prev->next = e->next;
                e->next->prev = e->prev;
                e->next = e->prev = NULL;
                destroy_Enemy( e );
                continue;
            }
        }
        e->p.e.p.x -= e->speedX;
        if (update_Enemy( e, player, app, renderer )) return;
    }
    appearance( list, renderer );
}

void destroy_Enemy( Enemy *enemy ) {
    destroy_Bullets( &enemy->p.bullet );
    destroy_Player( &enemy->p );
    free( enemy );
    enemy = NULL;
}

static void appearance( ListEnemies *list, SDL_Renderer *renderer ) {
    if ( enemyAppearance-- >= 0 ) return;
    Enemy *enemy = load_Enemy( renderer );
    add_Enemy( list, enemy );
}

static Enemy *load_Enemy( SDL_Renderer *renderer ) {
    Enemy *enemy = (Enemy *)malloc( sizeof(Enemy) );
    load_Player(
        &enemy->p,
        renderer,
        "assets/enemy.png",
        SCREEN_W, (rand() % ((SCREEN_H - 46) - 46 + 1)) + 46,
        48, 46
    );

    enemy->next = enemy->prev = NULL;
    enemy->speedX = 1.0f;
    enemy->speedY = 0.0f;
    enemyAppearance = 150;

    return enemy;
}

static void  add_Enemy( ListEnemies *list, Enemy *enemy ) {
    if (list->first == NULL && list->last == NULL)
        list->first = list->last = enemy;
    else {
        enemy->prev = list->last;
        list->last->next = enemy,
        list->last = enemy;
    }
}

static bool hit_Bullet( Enemy *e, ListBullet *list ) {
    for (Bullet *b = list->first; b != NULL; b = b->next) {
        if (collision(b->e.p.x, b->e.p.y, b->e.p.w, b->e.p.h, e->p.e.p.x, e->p.e.p.y, e->p.e.p.w, e->p.e.p.h)) {
            scoreValue++;
            b->isVisible = false;
            return true;
        }
    }
    return false;
}

static bool update_Enemy( Enemy *e, Player *p, App *app, SDL_Renderer *renderer ) {
    for (Bullet *b = e->p.bullet.first; b != NULL; b = b->next) {
        if (collision(b->e.p.x, b->e.p.y, b->e.p.w, b->e.p.h, p->e.p.x, p->e.p.y, p->e.p.w, p->e.p.h)) {
            app->state = RELOAD;
            return true;
        }
    }
    if ( shootingTimer-- <= 0 ) {
        fire( e, renderer);
        shootingTimer = 350;
    }
    update_Bullet( &e->p.bullet, condition, callback );
    return false;
}

static void fire( Enemy *e, SDL_Renderer *renderer ) {
    Bullet *b =load_Bullet(
        renderer,
        "assets/enemyBullet.png",
        e->p.e.p.x + 26, e->p.e.p.y + (e->p.e.p.h / 2) - 5,
        26, 9
    );

    if (e->p.bullet.first == NULL && e->p.bullet.last == NULL) {
        e->p.bullet.first = b;
        e->p.bullet.last = b;
    } else {
        b->next = e->p.bullet.first;
        e->p.bullet.first->prev = b;
        e->p.bullet.first = b;
    }
}

static void callback( Bullet *bullet ) {
    bullet->e.p.x -= bullet->speed;
}

static bool condition( Bullet *bullet ) {
    return bullet->e.p.x < 0 || !bullet->isVisible;
}