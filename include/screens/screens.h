#ifndef SCREENS_h
#define SCREENS_h

#include <raylib.h>

typedef enum GameScreen{TITLE=0, GAMEPLAY} GameScreen;
extern GameScreen currentScreen;

void TitleScreen(void);
void GameplayScreen(void);

#endif


