#include <stdlib.h>
#include <math.h>
#include "enemy/enemy.h"
#include "window_config/window_config.h"
#include "points/points.h"
#include "screens/screens.h"

int speedMultiplier;
float enemyCooldown=1;
int enemiesAlive;
Enemy *enemiesList = NULL;

void CreateEnemy(void)
{
	if(enemyCooldown<=0)
	{
		Enemy *enemy = malloc(sizeof(Enemy));
		if(enemy==NULL){TraceLog(LOG_ERROR, "Create Enemy malloc failed");}
		InitEnemy(enemy);
		enemyCooldown=5;
	}
	else{enemyCooldown-=dt;}
}

//FUNCTION THAT INITIALIZES ENEMY
void InitEnemy(Enemy *enemy) 
{
	enemiesAlive++;

	//GENERATES A RANDOM NUMBER BETWEEN 1 AND 4 TO DEFINE WHICH POSITION SHOULD THE ENEMY SPAWN
	int randomPos = (rand() % 4) + 1;

	//VERIFIES WHICH NUMBER WAS GENERATED
	switch(randomPos)
	{
		//DEFINES ENEMY POSITION BASED ON THE GENERATED NUMBER
		case 1:{enemy->pos = (Vector2){-ENEMY_SIZE, -ENEMY_SIZE}; break;}
		case 2:{enemy->pos = (Vector2){-ENEMY_SIZE, SCREEN_HEIGHT + ENEMY_SIZE}; break;}
		case 3:{enemy->pos = (Vector2){SCREEN_WIDTH + ENEMY_SIZE, -ENEMY_SIZE}; break;}
		case 4:{enemy->pos = (Vector2){SCREEN_WIDTH, SCREEN_HEIGHT}; break;}
		default: break;
    	}

	SpawnEnemy(enemy);

	//DEFINES ENEMY PARAMETERS
    	enemy->size = ENEMY_SIZE;
    	enemy->rec = (Rectangle){enemy->pos.x + enemy->size/4, enemy->pos.y + enemy->size/4, enemy->size/2, enemy->size/2};

	UpdateEnemySpeed(enemy);

	UpdateEnemiesList(*enemy, &enemiesList);
}

void UpdateEnemiesList(Enemy enemy, Enemy **enemiesList)
{
	*enemiesList = realloc(*enemiesList, sizeof(Enemy) * enemiesAlive);
	if(enemiesList==NULL){TraceLog(LOG_ERROR, "Update Enemy list realloc failed");}
	(*enemiesList)[enemiesAlive - 1] = enemy;
}

//FUNCTION THAT DRAWS THE ENEMY
void DrawEnemies(void)
{
	if(enemiesList==NULL){return;}

	for(int i=0; i<enemiesAlive; i++)
	{
		DrawAnimatedSprite(enemiesList[i].animSprite);
	}
}

//FUNCTION THAT UPDATES THE ENEMY SPEED
void UpdateEnemySpeed(Enemy *enemy)
{
	speedMultiplier = 1 + (points/100);
	//MULTIPLY THE ENEMY SPEED BY THE NUMBER OF POINTS
	enemy->speed *= speedMultiplier;
}

//FUNCTION THAT MOVES THE ENEMY
void MoveEnemies(void)
{
	//CREATES THE POSITION OF THE SCREEN CENTER
	Vector2 screenCenter = {SCREEN_WIDTH/2, SCREEN_HEIGHT/2};

	for(int i=0; i<enemiesAlive; i++)
	{
		Enemy *enemy = &enemiesList[i];
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
	
		if((distanceX/distance)>0){SetAnimatedSpriteDir(&enemy->animSprite, 1);}
		else{SetAnimatedSpriteDir(&enemy->animSprite, 0);}

		UpdateAnimatedSprite(&enemy->animSprite);
		UpdateAnimatedSpritePos(&enemy->animSprite, enemy->pos);
	}

	CheckForEnemyDamage(&towerAttack);
}

//FUNCTION THAT UPDATES THE ENEMY RECTANGLE
void UpdateEnemyRec(Enemy *enemy)
{
	enemy->rec.x = enemy->pos.x + enemy->size/4;
	enemy->rec.y = enemy->pos.y + enemy->size/4;
}

void CheckForEnemyDamage(TowerAttack *towerAttack)
{
	for(int i=0; i<enemiesAlive; i++)
	{
		if(CheckCollisionRecs(towerAttack->rec, enemiesList[i].rec) && towerAttack->isAttacking == 1 && towerAttack->cooldown<=0)
		{
			DamageEnemy(&enemiesList[i]);
			ResetAttackCooldown(towerAttack);

			if(enemiesList[i].health<1){RemoveEnemy(i); IncreasePoints(1);}
		}
		if(CheckCollisionRecs(tower.rec, enemiesList[i].rec))
		{
			CheckAndUpdateMaxPoints(); 
			DeleteFireDecorations();
			DeleteEnemies(); 
			currentScreen=TITLE;
		}
	}
}

//FUNCTION THAT DAMAGES THE ENEMY
void DamageEnemy(Enemy *enemy)
{
	//REDUCES PLAYER HEALTH AND KILLS ENEMY IF BELLOW ZERO
	enemy->health -= 1;
}

void RemoveEnemy(int index)
{
	if(enemiesAlive<=0){return;}

	UnloadAnimatedSpriteTex(&enemiesList[index].animSprite);

	enemiesList[index] = enemiesList[enemiesAlive-1];
	enemiesAlive--;

	if(enemiesAlive>0)
	{
		Enemy *tmp = realloc(enemiesList, sizeof(Enemy) * enemiesAlive);
		if(tmp==NULL){TraceLog(LOG_ERROR, "Remove Enemy first realloc failed");}
		enemiesList = tmp;
	}
	else
	{
		free(enemiesList);
		enemiesList = NULL;
	}

	enemiesList = realloc(enemiesList, sizeof(Enemy) * enemiesAlive);
	if(enemiesList==NULL){TraceLog(LOG_ERROR, "Remove Enemy second realloc failed");}
}

//FUNCTION THAT SPAWNS THE ENEMY
void SpawnEnemy(Enemy *enemy)
{
	//GENERATES A RANDOM NUMBER BETWEEN 1 AND THE NUMBER OF ENEMIES CREATED TO VERIFY WHICH ENEMY WILL SPAWN
	int iChosenEnemy = (rand() % ENEMY_NUMBER) + 1;

	AnimatedSprite animSprite;

	//VERIFIES WHICH ENEMY WAS CHOSEN
	switch(iChosenEnemy)
	{
		case 1:{InitAnimatedSprite(&animSprite, LoadImage("assets/images/enemies/ghost.png"), 4, 0.2f); enemy->health=1; enemy->speed=0.5;  break;}
		case 2:{InitAnimatedSprite(&animSprite, LoadImage("assets/images/enemies/skeleton.png"), 5, 0.15f); enemy->health=2; enemy->speed=0.25;  break;}
	}

	enemy->animSprite = animSprite;
}

void DeleteEnemies(void)
{
	if(enemiesList!=NULL)
	{
		for(int i=0; i<enemiesAlive; i++)
		{
			UnloadAnimatedSpriteTex(&enemiesList[i].animSprite);
		}

		free(enemiesList);
		enemiesList=NULL;
		enemiesAlive=0;
	}
}
