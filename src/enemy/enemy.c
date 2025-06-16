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
Enemy boss;
char bossHealthText[32];

void CreateEnemy(void)
{
	if(enemyCooldown<=0)
	{
		Enemy *enemy = malloc(sizeof(Enemy));
		if(enemy==NULL){TraceLog(LOG_ERROR, "Create Enemy malloc failed");}
		InitEnemy(enemy);
		enemyCooldown=3;
	}
	else{enemyCooldown-=dt;}
}

void CreateBoss(Enemy *boss)
{
	if(points % 15 == 0 && points!=0 && boss->health<=0)
	{
		InitBoss(boss);
	}
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
		//TOP LEFT CORNER
		case 1:{enemy->pos = (Vector2){-ENEMY_SIZE, -ENEMY_SIZE}; break;}
		//BOTTOM LEFT CORNER
		case 2:{enemy->pos = (Vector2){-ENEMY_SIZE, SCREEN_HEIGHT}; break;}
		//TOP RIGHT CORNER
		case 3:{enemy->pos = (Vector2){SCREEN_WIDTH, -ENEMY_SIZE}; break;}
		//BOTTOM RIGHT CORNER
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

void InitBoss(Enemy *boss)
{
	int randomPos = (rand() % 4) + 1;

	switch(randomPos)
	{
		case 1:{boss->pos = (Vector2){SCREEN_WIDTH/2 - (ENEMY_SIZE/2), -ENEMY_SIZE}; break;}
		case 2:{boss->pos = (Vector2){SCREEN_WIDTH/2 - (ENEMY_SIZE/2), SCREEN_HEIGHT + ENEMY_SIZE}; break;}
		case 3:{boss->pos = (Vector2){-ENEMY_SIZE, SCREEN_HEIGHT/2 - (ENEMY_SIZE/2)}; break;}
		case 4:{boss->pos = (Vector2){SCREEN_HEIGHT + ENEMY_SIZE, SCREEN_HEIGHT/2 - (ENEMY_SIZE/2)}; break;}
		default: break;
	}

	SpawnBoss(boss);

	boss->size = ENEMY_SIZE;
	boss->rec = (Rectangle){boss->pos.x + boss->size/4, boss->pos.y + boss->size/4, boss->size/2, boss->size/2};

	UpdateEnemySpeed(boss);
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

void DrawBoss(Enemy boss)
{
	if(boss.health>0)
	{
		sprintf(bossHealthText, "Boss Health: %d", boss.health);
		DrawText(bossHealthText, SCREEN_WIDTH/2 - 60, SCREEN_HEIGHT/3 - 12, 24, PDARKRED);
	}

	DrawAnimatedSprite(boss.animSprite);
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

void MoveBoss(Enemy *boss)
{
	Vector2 screenCenter = {SCREEN_WIDTH/2, SCREEN_HEIGHT/2};

	float distanceX = screenCenter.x - boss->pos.x;
	float distanceY = screenCenter.y - boss->pos.y;
	float distance = sqrtf(distanceX*distanceX + distanceY*distanceY);

	boss->pos.x += (distanceX / distance) * boss->speed;
	boss->pos.y += (distanceY / distance) * boss->speed;

	UpdateEnemyRec(boss);

	if((distanceX/distance)>0){SetAnimatedSpriteDir(&boss->animSprite, 1);}
	else{SetAnimatedSpriteDir(&boss->animSprite, 0);}

	UpdateAnimatedSprite(&boss->animSprite);
	UpdateAnimatedSpritePos(&boss->animSprite, boss->pos);

	CheckForBossDamage(boss, &towerAttack);
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
			PlayEnemyDamageSound();
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

void CheckForBossDamage(Enemy *boss, TowerAttack *towerAttack)
{
	if(CheckCollisionRecs(boss->rec, towerAttack->rec) && towerAttack->isAttacking==1 && towerAttack->cooldown<=0)
	{
		DamageEnemy(boss);
		PlayEnemyDamageSound();
		ResetAttackCooldown(towerAttack);

		if(boss->health<1){DeleteBoss(boss); IncreasePoints(1);}
	}
	if(CheckCollisionRecs(boss->rec, tower.rec))
	{
		CheckAndUpdateMaxPoints();
		DeleteFireDecorations();
		DeleteBoss(boss);
		currentScreen=TITLE;
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
	AnimatedSprite animSprite;

	int enemyNumber;
	if(points>=0 && points<=10){enemyNumber=1;}
	else if(points>=11 && points<=20){enemyNumber=2;}
	else if(points>=21 && points<=30){enemyNumber=3;}
	else{enemyNumber=3;}

	//GENERATES A RANDOM NUMBER BETWEEN 1 AND THE NUMBER OF ENEMIES CREATED TO VERIFY WHICH ENEMY WILL SPAWN
	int chosenEnemy = (rand() % enemyNumber) + 1;

	//VERIFIES WHICH ENEMY WAS CHOSEN
	switch(chosenEnemy)
	{
		case 1:{InitAnimatedSprite(&animSprite, LoadImage("assets/images/enemies/ghost.png"), 4, 0.2f); enemy->health=1; enemy->speed=0.5;  break;}
		case 2:{InitAnimatedSprite(&animSprite, LoadImage("assets/images/enemies/skeleton.png"), 5, 0.15f); enemy->health=2; enemy->speed=0.25;  break;}
		case 3:{InitAnimatedSprite(&animSprite, LoadImage("assets/images/enemies/spider.png"), 8, 0.1f); enemy->health=2; enemy->speed=0.75;  break;}
		default: break;
	}

	enemy->animSprite = animSprite;
}

void SpawnBoss(Enemy *boss)
{
	AnimatedSprite animSprite;

	int bossNumber;
	if(points>=15 && points<=29){bossNumber=1;}
	else if(points>=30 && points<=44){bossNumber=2;}
	else{bossNumber=2;}

	int chosenBoss = (rand() % bossNumber) + 1;
	switch(chosenBoss)
	{
		case 1:
			{
				InitAnimatedSprite(&animSprite, LoadImage("assets/images/enemies/eye_of_truth.png"), 2, 0.4f);
				boss->health = 10;
				boss->speed = 0.2f;
				break;
			}
		case 2:
			{
				InitAnimatedSprite(&animSprite, LoadImage("assets/images/enemies/reaper.png"), 1, 0.0f);
				boss->health = 5;
				boss->speed = 0.4f;
				break;
			}
		default: break;
	}

	boss->animSprite = animSprite;
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

void DeleteBoss(Enemy *boss)
{
	if(boss!=NULL)
	{
		UnloadAnimatedSpriteTex(&boss->animSprite);
		*boss = (Enemy){0};
	}
}
