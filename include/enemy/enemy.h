#ifndef ENEMY_H
#define ENEMY_H

#include "raylib.h"
#include "animated_sprite/animated_sprite.h"
#include "points/points.h"
#include "tower/tower.h"
#include "tower/tower_attack/tower_attack.h"
#include "fire_decorations/fire_decorations.h"
#include "color_palette/color_palette.h"
#include "sounds/sounds.h"

#define ENEMY_SIZE 64

//DEFINES THE ENEMY STRUCTURE
typedef struct Enemy 
{
	int health;
	Vector2 pos;
	float speed;
	float size;
	Rectangle rec;
	AnimatedSprite animSprite;
} Enemy;

extern int speedMultiplier;
extern float enemyCooldown;
extern int enemiesAlive;
extern Enemy *enemiesList;
extern Enemy boss;
extern char bossHealthText[32];

//DEFINES THE ENEMY FUNCTIONS
void CreateEnemy(void);
void CreateBoss(Enemy *boss);
void InitEnemy(Enemy *enemy);
void InitBoss(Enemy *boss);
void UpdateEnemiesList(Enemy enemy, Enemy **enemiesList);
void DrawEnemies(void);
void DrawBoss(Enemy boss);
void UpdateEnemySpeed(Enemy *enemy);
void MoveEnemies(void);
void MoveBoss(Enemy *boss);
void UpdateEnemyRec(Enemy *enemy);
void CheckForEnemyDamage(TowerAttack *towerAttack);
void CheckForBossDamage(Enemy *boss, TowerAttack *towerAttack);
void DamageEnemy(Enemy *enemy);
void RemoveEnemy(int index);
void SpawnEnemy(Enemy *enemy);
void SpawnBoss(Enemy *boss);
void DeleteEnemies(void);
void DeleteBoss(Enemy *boss);

#endif
