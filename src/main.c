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

	//RANDOMIZE RANDOM SEED
	srand(time(NULL));

	//INITIALIZE THE TITTLE SCREEN LETTERING
	Image tittleLetteringImg = LoadImage("assets/images/letterings/tittle_screen.png");
	Texture2D tittleLetteringTex = LoadTextureFromImage(tittleLetteringImg);

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

	//INITIALIZE THE FIRE DECORATIONS VARIABLES
	int firesGenerated = 0;
	int fireNumber;
	FireDecoration *fireList;

	//INITIALIZE THE VARIABLE THAT CONTROLS THE GAME
	int game = 1;

	while (game==1)
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
				if(firesGenerated==1)
				{
					free(fireList);
					firesGenerated=0;
				}

				BeginDrawing();

            			ClearBackground(PORANGE);

				DrawTextureV(tittleLetteringTex, (Vector2){0 + 48, 100}, WHITE);

				DrawText(maxPointsText, 0, 0, 24, PDARKRED);
				
				//VERIFIES IF PLAY GUI BUTTON WAS PRESSED
				if(GuiButton((Rectangle){SCREEN_WIDTH/2 - 100, SCREEN_HEIGHT/2 + 50, 200, 100}, "PLAY"))
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

				//VERIFIES IF EXIT GUI BUTTON WAS PRESSED
				if(GuiButton((Rectangle){SCREEN_WIDTH/2 - 100, SCREEN_HEIGHT/2 + 150, 200, 100}, "EXIT")){game = 0;}

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
					//GENERATE A RANDOM NUMBER OF FIRES AND ALLOCATE IT TO THE MEMORY
					fireNumber = (rand() % 4) + 1;
					fireList = malloc(sizeof(FireDecoration) * fireNumber);

					for(int i=0; i<fireNumber; i++)
					{
						//GENERATE A RANDOM FIRE POSITION
						Vector2 randomPos = {(rand() % SCREEN_WIDTH) + 1, (rand() % SCREEN_HEIGHT) + 1};

						//SPAWN THE FIRE
						FireDecoration fire;
						InitFireDecoration(&fire, randomPos);
						fireList[i] = fire;
					}

					firesGenerated = 1;
				}
				else
				{
					for(int i=0; i<fireNumber; i++)
					{
						//UPDATE AND DRAWS FIRE DECORATIONS
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

	if(firesGenerated==1)
	{
		//REMOVES THE FIRE DECORATIONS FROM THE MEMORY
		free(fireList);
	}

	//CLOSE WINDOW AND FINISH THE GAME
	CloseWindow();
	return 0;
}
