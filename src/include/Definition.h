#ifndef _DEFITION_H_
#define _DEFITION_H_

typedef     struct _App                 App;
typedef     enum   _AppState            AppState;
typedef     struct _BackgroundStart     BackgroundStart;
typedef     struct _AppBackground       AppBackground;

typedef     struct _Player              Player;
typedef     struct _PlayerDelegate      PlayerDelegate;

typedef     struct _Entity              Entity;
typedef     struct _Properties          Properties;

typedef     struct _Enemy               Enemy;
typedef     struct _ListEnemies         ListEnemies;

typedef     struct _Bullet              Bullet;
typedef     struct _ListBullet          ListBullet;
typedef     struct _BulletDelegate      BulletDelegate;

typedef     struct _Explosion           Explosion;
typedef     struct _ListExplosion       ListExplosion;
typedef     struct _Debris              Debris;
typedef     struct _ListDebris          ListDebris;

typedef     struct _Score               Score;


#define     SCREEN_W                    1280
#define     SCREEN_H                    600 
#define     MAX_STARS                   500

#define     GLYPH_HEIGHT                28
#define     GLYPH_WIDTH                 18     

#define     MAX(a, b)                   (((a) > (b)) ? (a) : (b))
#define     MIN(a, b)                   (((a) < (b)) ? (a) : (b))

#endif