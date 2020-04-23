#include "Common.h"

static long long int elapsedTime = 0;
long long int scoreValue = 0;
static Score score;

static void move_x( Player *player, const float newPosition );
static void move_y( Player *player, const float newPosition );
static void fire( Player *player, SDL_Renderer *renderer );

static void callback( Bullet *bullet );
static bool condition( Bullet *bullet );

void load_Player( Player *player, SDL_Renderer *renderer, const char *textureName, const float x, const float y, const float w, const float h  ) {
    player->e.p.x = x;
    player->e.p.y = y;
    player->e.p.w = w;
    player->e.p.h = h;
    player->e.texture = IMG_LoadTexture( renderer, textureName );
    player->bullet.first = NULL;
    player->bullet.last = NULL;
    score = load_Score();

    // Bind
    player->method.blit_Player = blit_Player;
    player->method.event_Handler = event_Handler;
    player->method.update_Player = update_Player;
}

void destroy_Player( Player *player ) {
    destroy_Score( &score );
    destroy_Bullets( &player->bullet );
    SDL_DestroyTexture( player->e.texture );
}

void blit_Player( Player *player, SDL_Renderer *renderer ) {
    for (Bullet *b = player->bullet.first; b != NULL; b = b->next) {
        b->method.blit_Bullet( b, renderer );
    }

	SDL_Rect dest;
	dest.x = player->e.p.x;
	dest.y = player->e.p.y;
	SDL_QueryTexture(player->e.texture, NULL, NULL, &dest.w, &dest.h);
	SDL_RenderCopy(renderer, player->e.texture, NULL, &dest);

    blit_Score( &score, renderer );

    if (elapsedTime != 0) elapsedTime--;
}

void event_Handler( Player *player, const Uint8 *keyState, SDL_Renderer *renderer ) {
    if (keyState[SDL_SCANCODE_SPACE]) {
        fire( player, renderer );
    }
    if (keyState[SDL_SCANCODE_RIGHT]) {
        move_x(
            player,
            player->e.p.x + 10
        );
    }
    if (keyState[SDL_SCANCODE_LEFT]) {
        move_x(
            player,
            player->e.p.x - 10
        );
    }
    if (keyState[SDL_SCANCODE_UP]) {
        move_y(
            player,
            player->e.p.y - 10
        );
    }
    if (keyState[SDL_SCANCODE_DOWN]) {
        move_y(
            player,
            player->e.p.y + 10
        );
    }
}

void update_Player( Player *player ) {
    update_Bullet( &player->bullet, condition, callback );
    score.currentScore = scoreValue;
    if (score.currentScore > score.higherScore)
        score.higherScore = score.currentScore;
}

static void move_x( Player *player, const float newPosition ){
    if (newPosition >= 0 && newPosition < (SCREEN_W - player->e.p.w)) 
        player->e.p.x = newPosition;
}

static void move_y( Player *player, const float newPosition ){
    if (newPosition > 0 && newPosition < (SCREEN_H - player->e.p.h))
        player->e.p.y = newPosition;
}

static void fire( Player *player, SDL_Renderer *renderer ) {
    if (elapsedTime <= 0) {
        elapsedTime = 100;
        Bullet *b =load_Bullet(
            renderer,
            "assets/playerBullet.png",
            player->e.p.x + 26, player->e.p.y + (player->e.p.h / 2) - 5,
            26, 9
        );

        if (player->bullet.first == NULL && player->bullet.last == NULL) {
            player->bullet.first = b;
            player->bullet.last = b;
        } else {
            b->next = player->bullet.first;
            player->bullet.first->prev = b;
            player->bullet.first = b;
        }
    }
}

static void callback( Bullet *bullet ) {
    bullet->e.p.x += bullet->speed;
}

static bool condition( Bullet *bullet ) {
    return bullet->e.p.x > SCREEN_W || !bullet->isVisible;
}