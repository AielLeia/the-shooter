CC					:= gcc
EXE					:= bin/Shooter


OBJ					:= src/obj
SRC					:= src
INCLUDE				:= -Iinclude -Isrc/include
LIB					:= -Llib -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf

MAIN_SRC			:= Main.c
MAIN_OBJ			:= Main.obj

SHOOTER_SRC			:= Shooter.c
SHOOTER_OBJ			:= Shooter.obj

PLAYER_SRC			:= Player.c
PLAYER_OBJ			:= Player.obj

BULLET_SRC			:= Bullet.c
BULLET_OBJ			:= Bullet.obj

ENEMY_SRC			:= Enemies.c
ENEMY_OBJ			:= Enemies.obj

UTILS_SRC			:= Utils.c
UTILS_OBJ			:= Utils.obj

EFFECT_SRC			:= Effect.c
EFFECT_OBJ			:= Effect.obj

SCORE_SRC			:= Score.c
SCORE_OBJ			:= Score.obj



$(EXE): $(OBJ)/$(SHOOTER_OBJ) $(OBJ)/$(BULLET_OBJ) $(OBJ)/$(PLAYER_OBJ) $(OBJ)/$(ENEMY_OBJ) $(OBJ)/$(UTILS_OBJ) $(OBJ)/$(EFFECT_OBJ) $(OBJ)/$(SCORE_OBJ) $(OBJ)/$(MAIN_OBJ)
	$(CC) -o $(EXE) -g $^ $(LIB)

$(OBJ)/%.obj: $(SRC)/%.c src/include/*
	$(CC) -o $@ -c -g $< $(INCLUDE)

run: $(EXE)
	$(EXE)