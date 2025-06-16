#ifndef SOUNDS_H
#define SOUNDS_H

#include "raylib.h"

extern Music backgroundMusic;
extern Sound enemyDamage;

void CreateSounds(void);
void StartMusic(void);
void UpdateMusic(void);
void PlayEnemyDamageSound(void);
void UnloadSounds(void);

#endif
