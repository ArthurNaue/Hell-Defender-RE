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
#include "tower/tower_attack/tower_attack.h"
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

	float enemyCooldown = 1;

	//INITIALIZE THE POINTS
	InitPoints();
	
	//INITIALIZE THE TOWER AND THE TOWERS ATTACK
	Tower tower;
	InitTower(&tower);
	InitTowerAttack(&towerAttack);

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
				if(enemyCooldown<=0)
				{
					CreateEnemy();
					enemyCooldown = 5;
				}
				else{enemyCooldown -= dt;}

				if(IsKeyPressed(KEY_ESCAPE)){CheckAndUpdateMaxPoints(); currentScreen = TITLE;}

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

				DrawEnemies();
				MoveEnemies();

				UpdateTowerAttack(&towerAttack);

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

	if(enemiesList!=NULL){free(enemiesList);}
	//CLOSE WINDOW AND FINISH THE GAME
	CloseWindow();
	return 0;
}
