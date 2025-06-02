#include <stdlib.h>
#include <math.h>
#include "enemy/enemy.h"
#include "window_config/window_config.h"
#include "points/points.h"

int speedMultiplier;

//FUNCTION THAT INITIALIZES ENEMY
void InitEnemy(Enemy *enemy) 
{
	//GENERATES A RANDOM NUMBER BETWEEN 1 AND 8 TO DEFINE WHICH POSITION SHOULD THE ENEMY SPAWN
	int randomPos = (rand() % 8) + 1;

	//VERIFIES WHICH NUMBER WAS GENERATED
	switch(randomPos)
	{
		//DEFINES ENEMY POSITION BASED ON THE GENERATED NUMBER
		case 1:{enemy->pos = (Vector2){0, 0}; break;}
		case 2:{enemy->pos = (Vector2){0, SCREEN_HEIGHT}; break;}
		case 3:{enemy->pos = (Vector2){0, SCREEN_HEIGHT/2}; break;}
		case 4:{enemy->pos = (Vector2){SCREEN_WIDTH, 0}; break;}
		case 5:{enemy->pos = (Vector2){SCREEN_WIDTH/2, 0}; break;}
		case 6:{enemy->pos = (Vector2){SCREEN_WIDTH, SCREEN_HEIGHT/2}; break;}
		case 7:{enemy->pos = (Vector2){SCREEN_WIDTH/2, SCREEN_HEIGHT}; break;}
		case 8:{enemy->pos = (Vector2){SCREEN_WIDTH, SCREEN_HEIGHT}; break;}
		default: break;
    	}

	//GENERATES A RANDOM NUMBER BETWEEN 1 AND THE NUMBER OF ENEMIES CREATED TO VERIFY WHICH ENEMY WILL SPAWN
	int iChosenEnemy = (rand() % ENEMY_NUMBER) + 1;

	//VERIFIES WHICH ENEMY WAS CHOSEN
	switch(iChosenEnemy)
	{
		case 1:{enemy->img = LoadImage("assets/images/enemies/ghost.png"); enemy->health=1; enemy->speed=2;  break;}
		case 2:{enemy->img = LoadImage("assets/images/enemies/skeleton.png"); enemy->health=2; enemy->speed=1;  break;}
	}

	//DEFINES ENEMY PARAMETERS
    	enemy->size = ENEMY_SIZE;
    	enemy->color = RED;
    	enemy->rec = (Rectangle){enemy->pos.x, enemy->pos.y, enemy->size, enemy->size};
    	enemy->tex = LoadTextureFromImage(enemy->img);

	UpdateEnemySpeed(enemy);

	UnloadImage(enemy->img);
}

//FUNCTION THAT DRAWS THE ENEMY
void DrawEnemy(Enemy enemy)
{
	//DRAW THE ENEMY TEXTURE
	DrawTextureV(enemy.tex, enemy.pos, WHITE);
}

//FUNCTION THAT UPDATES THE ENEMY SPEED
void UpdateEnemySpeed(Enemy *enemy)
{
	speedMultiplier = 1 + (points/100);
	//MULTIPLY THE ENEMY SPEED BY THE NUMBER OF POINTS
	enemy->speed *= speedMultiplier;
}

//FUNCTION THAT MOVES THE ENEMY
void MoveEnemy(Enemy *enemy)
{
	//CREATES THE POSITION OF THE SCREEN CENTER
	Vector2 screenCenter = {SCREEN_WIDTH/2, SCREEN_HEIGHT/2};

	//GET THE DISTANCE BETWEEN THE ENEMY AND THE TOWER
	float distanceX = screenCenter.x  - enemy->pos.x;
	float distanceY = screenCenter.y - enemy->pos.y;
	//APPLY PITAGORAS TO PREVENT FASTER WALKING IN DIAGONALS
	float distance = sqrtf(distanceX*distanceX + distanceY*distanceY);

	//ADDS THE DIRECTION THE ENEMY SHOULD FOLLOW TO THE ENEMYS POSITION
	enemy->pos.x += (distanceX / distance) * enemy->speed;
	enemy->pos.y += (distanceY / distance) * enemy->speed;

	//UPDATED THE ENEMY RECTANGLE TO FOLLOW ENEMYS POSITION
	UpdateEnemyRec(enemy);
}

//FUNCTION THAT UPDATES THE ENEMY RECTANGLE
void UpdateEnemyRec(Enemy *enemy)
{
	enemy->rec.x = enemy->pos.x;
	enemy->rec.y = enemy->pos.y;
}

//FUNCTION THAT DAMAGES THE ENEMY
void DamageEnemy(Enemy *enemy)
{
	//REDUCES PLAYER HEALTH AND KILLS ENEMY IF BELLOW ZERO
	enemy->health -= 1;
}

//FUNCTIONS THAT KILL THE ENEMY
void KillEnemy(Enemy *enemy)
{
	UnloadTexture(enemy->tex);
}
