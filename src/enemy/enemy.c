#include <stdlib.h>
#include "enemy/enemy.h"
#include "window_config/window_config.h"

void InitEnemy(Enemy *enemy) 
{
    int randomPos = (rand() % 8) + 1;

    switch(randomPos)
    {
	case 1:{enemy->pos = (Vector2){0, 0}; break;}
	case 2:{enemy->pos = (Vector2){0, SCREEN_HEIGHT};break;}
	case 3:{enemy->pos = (Vector2){0, SCREEN_HEIGHT/2};break;}
	case 4:{enemy->pos = (Vector2){SCREEN_WIDTH, 0};break;}
	case 5:{enemy->pos = (Vector2){SCREEN_WIDTH/2, 0}; break;}
	case 6:{enemy->pos = (Vector2){SCREEN_WIDTH, SCREEN_HEIGHT/2};break;}
	case 7:{enemy->pos = (Vector2){SCREEN_WIDTH/2, SCREEN_HEIGHT};break;}
	case 8:{enemy->pos = (Vector2){SCREEN_WIDTH, SCREEN_HEIGHT};break;}
	default: break;
    }

    enemy->speed = 2;
    enemy->size = 25;
    enemy->color = RED;
    enemy->rec = (Rectangle){enemy->pos.x, enemy->pos.y, enemy->size, enemy->size};
    enemy->img = LoadImage("assets/images/enemies/ghost/ghost.png");
    enemy->tex = LoadTextureFromImage(enemy->img);
}

void DrawEnemy(Enemy enemy)
{
	DrawTextureV(enemy.tex, enemy.pos, WHITE);
}

void MoveEnemy(Enemy *enemy, Tower *tower)
{
	Vector2 truePos = {enemy->pos.x - (enemy->size/2), enemy->pos.y - (enemy->size/2)};

	if(truePos.x > tower->pos.x){enemy->pos.x -= enemy->speed;}
	if(truePos.x < tower->pos.x){enemy->pos.x += enemy->speed;}
	if(truePos.y > tower->pos.y){enemy->pos.y -= enemy->speed;}
	if(truePos.y < tower->pos.y){enemy->pos.y += enemy->speed;}

	UpdateEnemyRec(enemy);
}

void UpdateEnemyRec(Enemy *enemy)
{
	enemy->rec.x = enemy->pos.x;
	enemy->rec.y = enemy->pos.y;
}
