#include "sounds/sounds.h"

Music backgroundMusic;
Sound enemyDamage;

void CreateSounds(void)
{
	backgroundMusic = LoadMusicStream("assets/sounds/background_music.wav");
	enemyDamage = LoadSound("assets/sounds/enemyDamage.wav");
}

void StartMusic(void)
{
	PlayMusicStream(backgroundMusic);
}

void UpdateMusic(void)
{
	UpdateMusicStream(backgroundMusic);
}

void UnloadSounds(void)
{
	UnloadMusicStream(backgroundMusic);
	UnloadSound(enemyDamage);
}
