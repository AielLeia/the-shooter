#include "Common.h"

extern long long int scoreValue;

static void blitRect(SDL_Texture *texture, SDL_Renderer *renderer, SDL_Rect *src, int x, int y);

Score load_Score( SDL_Renderer *renderer ) {
    Score s;
    s.e.texture = IMG_LoadTexture( renderer, "assets/font.png" );
    s.e.p.x = s.e.p.y = s.e.p.w = s.e.p.h = 0;
    s.currentScore = 0;
    FILE *file = fopen( "assets/score/score.txt", "r" );
    fscanf( file, "%d", &s.higherScore);
    fclose(file);
    return s;
}

void destroy_Score( Score *s ) {
    FILE *file = fopen( "assets/score/score.txt", "w" );
    fprintf( file, "%d", s->higherScore);
    fclose(file);
    SDL_DestroyTexture( s->e.texture );
}

void blit_Score( Score *s, SDL_Renderer *renderer ) {
    SDL_Rect rect;
    char score[1024];
    char higherScore[1024];
    int len, x, y;

    memset(score, '\0', sizeof(score));
    memset(higherScore, '\0', sizeof(higherScore));

    sprintf(score, "SCORE: %03d", s->currentScore);
    sprintf(higherScore, "HIGH SCORE: %03d", s->higherScore);
    SDL_SetTextureColorMod(s->e.texture, 255, 255, 255);

    TTF_Font *font = TTF_OpenFont("assets/font/Inconsolata-Medium.ttf", 16);
    SDL_Surface *surface = TTF_RenderText_Solid( font, score, (SDL_Color){ .r = 255, .g = 255, .b = 255, .a = 255});
    SDL_Texture *message = SDL_CreateTextureFromSurface(renderer, surface);

    rect.x = 10;
    rect.y = 10;
    rect.h = 50;
    rect.w = 150;
    SDL_RenderCopy( renderer, message, NULL, &rect );
    SDL_FreeSurface( surface );
    SDL_DestroyTexture( message );

    SDL_Surface *surface2 = TTF_RenderText_Solid( font, higherScore, (SDL_Color){ .r = 255, .g = 255, .b = 255, .a = 255});
    SDL_Texture *message2 = SDL_CreateTextureFromSurface(renderer, surface2);

    rect.x = 1000;
    rect.y = 10;
    rect.h = 50;
    rect.w = 250;
    SDL_RenderCopy( renderer, message2, NULL, &rect );
    SDL_FreeSurface( surface2 );
    SDL_DestroyTexture( message2 );


    TTF_CloseFont( font );
}

void blitRect(SDL_Texture *texture, SDL_Renderer *renderer, SDL_Rect *src, int x, int y) {
	SDL_Rect dest;
	
	dest.x = x;
	dest.y = y;
	dest.w = src->w;
	dest.h = src->h;
	
	SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);
	SDL_RenderCopy(renderer, texture, src, &dest);
}