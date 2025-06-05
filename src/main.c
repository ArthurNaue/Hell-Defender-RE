#include <time.h>
#include "raylib.h"
#define RAYGUI_IMPLEMENTATION
#include "raygui/raygui.h"
#include "window_config/window_config.h"
#include "color_palette/color_palette.h"
#include "points/points.h"
#include "screens/screens.h"
#include "dt/dt.h"
#include "animated_sprite/animated_sprite.h"
#include "tower/tower.h"
#include "tower/towerAttack/towerAttack.h"
#include "enemy/enemy.h"
#include "fire_decorations/fire_decorations.h"

//DEFINE GAME SCREENS ENUM
gameScreen currentScreen = TITLE; 

int main(void)
{
	//WINDOW PARAMETERS
	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);
	SetTargetFPS(60);
	SetExitKey(KEY_NULL);

	srand(time(NULL));

	//INITIALIZE THE POINTS
	InitPoints();
	
	//INITIALIZE THE TOWER AND THE TOWERS ATTACK
	Tower tower;
	InitTower(&tower);
	TowerAttack towerAttack;
	InitTowerAttack(&towerAttack);

	//INITIALIZE THE ENEMY
	Enemy *enemy = malloc(sizeof(Enemy));
	InitEnemy(enemy);

	int firesGenerated = 0;
	int fireNumber;
	FireDecoration *fireList;

	while (!WindowShouldClose())
	{
		//UPDATES THE DELTA TIME
		UpdateDt();

		//ATUALIZA O TEXTO DOS PONTOS
		sprintf(pointsText, "Score: %d", points);
		//ATUALIZA O TEXTO DOS PONTOS MAXIMOS
		sprintf(maxPointsText, "Max Score: %d", maxPoints);
		//ATUALIZA O TEXTO DO COOLDOWN DO ATAQUE
		sprintf(attackCooldownText, "Cooldown: %d", towerAttack.cooldown);

		//VERIFIES CURRENT SCREEN
		switch(currentScreen)
		{
			case TITLE:
			{
				BeginDrawing();

            			ClearBackground(PORANGE);
				DrawText("HELL DEFENDER RE", SCREEN_WIDTH/2 - ((SCREEN_WIDTH/2)/2), SCREEN_HEIGHT/6, 24, PDARKRED);
				DrawText(maxPointsText, 0, 0, 24, PDARKRED);
				
				//VERIFIES IF GUI BUTTON WAS PRESSED
				if(GuiButton((Rectangle){SCREEN_WIDTH/2 - ((SCREEN_WIDTH/2)/2), SCREEN_HEIGHT/2 - ((SCREEN_HEIGHT/2)/2), SCREEN_WIDTH/2, SCREEN_HEIGHT/2}, "PLAY"))
				{
					if(enemy==NULL)
					{
						//IF NO ENEMY ALIVE, CREATE ONE
						enemy = malloc(sizeof(Enemy));
						InitEnemy(enemy);
					}
					//CHANGE SCREEN TO GAMEPLAY
					currentScreen=GAMEPLAY;
				}

        			EndDrawing();

				break;
			}
			case GAMEPLAY:
			{
				if(IsKeyPressed(KEY_ESCAPE)){free(enemy); enemy=NULL; currentScreen=TITLE; CheckAndUpdateMaxPoints();}

				//IF ENEMY EXISTS, MOVE IT AND CHECK IF PLAYER CLICKED ON IT, IF IT DID, KILL THE ENEMYMoveEnemy(enemy);
				if(enemy){MoveEnemy(enemy);}
				else
				{
					//IF NO PLAYER EXISTS, CREATE ONE
					enemy = malloc(sizeof(Enemy));
					InitEnemy(enemy);
				}
        			
				BeginDrawing();

				if(firesGenerated==0)
				{
					fireNumber = (rand() % 4) + 1;
					fireList = malloc(sizeof(FireDecoration) * fireNumber);

					for(int i=0; i<fireNumber; i++)
					{
						Vector2 randomPos = {(rand() % SCREEN_WIDTH) + 1, (rand() % SCREEN_HEIGHT) + 1};

						FireDecoration fire;
						InitFireDecoration(&fire, randomPos);
						fireList[i] = fire;
					}

					firesGenerated = 1;
				}
				else
				{
					for(int i=0; i<=fireNumber; i++)
					{
						UpdateFireDecoration(&fireList[i]);
						DrawFireDecoration(fireList[i]);
					}
				}

            			ClearBackground(PORANGE);
            			DrawTower(tower);
				DrawText(pointsText, 0, 0, 24, PDARKRED);
				DrawText(attackCooldownText, 0, SCREEN_HEIGHT-24, 24, PDARKRED);

				if(enemy)
				{
					DrawEnemy(*enemy);
					//VERIFIES IF TOWER ATTACK HITS ENEMY
					if(CheckCollisionRecs(towerAttack.rec, enemy->rec) && towerAttack.isAttacking==1 && towerAttack.cooldown<=0)
					{
						DamageEnemy(enemy);
						ResetAttackCooldown(&towerAttack);

						if(enemy->health<1){free(enemy); enemy=NULL; points++;}
					}
					//VERIFIES IF ENEMY TOUCHED THE TOWER AND ENDS THE GAME
					else if(CheckCollisionRecs(tower.rec, enemy->rec)){free(enemy); enemy=NULL; currentScreen=TITLE; CheckAndUpdateMaxPoints();}
				}

				//DRAW AND UPDATE TOWER ATTACK POSITION AND COOLDOWN
				UpdateAttack(&towerAttack);

				//USE THE TOWER ATTACK IF PLAYER HOLDS M1
				if(IsMouseButtonDown(MOUSE_BUTTON_LEFT)){TurnAttackOn(&towerAttack);}
				else{TurnAttackOff(&towerAttack);}

        			EndDrawing();
			
			       	break;
			} 
			default: break;
		}
	}

	free(fireList);

	//CLOSE WINDOW AND FINISH THE GAME
	CloseWindow();
	return 0;
}
