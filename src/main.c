#include "raylib.h"
#define RAYGUI_IMPLEMENTATION
#include "raygui/raygui.h"
#include "window_config/window_config.h"
#include "color_palette/color_palette.h"
#include "points/points.h"
#include "screens/screens.h"
#include "tower/tower.h"
#include "enemy/enemy.h"

//DEFINE GAME SCREENS ENUM
gameScreen currentScreen = TITLE; 

int main(void)
{
	//WINDOW PARAMETERS
	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);
	SetTargetFPS(60);
	SetExitKey(KEY_NULL);

	//INITIALIZE THE POINTS
	InitPoints();

	//CREATE GAME OBJECTS
	Tower tower;
	InitTower(&tower);
	Enemy *enemy = malloc(sizeof(Enemy));
	InitEnemy(enemy);

	while (!WindowShouldClose())
	{
		//VERIFIES CURRENT SCREEN
		switch(currentScreen)
		{
			case TITLE:
			{
				//ATUALIZA O TEXTO DOS PONTOS MAXIMOS
				sprintf(maxPointsText, "Max Score: %d", maxPoints);

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
				//ATUALIZA O TEXTO DOS PONTOS
				sprintf(pointsText, "Score: %d", points);

				if(IsKeyPressed(KEY_ESCAPE)){currentScreen=TITLE; CheckAndUpdateMaxPoints();}

				if(enemy)
				{
					//IF ENEMY EXISTS, MOVE IT AND CHECK IF PLAYER CLICKED ON IT, IF IT DID, KILL THE ENEMY
					MoveEnemy(enemy);	
					if(CheckCollisionPointRec(GetMousePosition(), enemy->rec))
					{
						if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
						{
							DamageEnemy(enemy);
							if(enemy->health<1)
							{
								KillEnemy(enemy);
								free(enemy);
								enemy = NULL;
								points++;
							}
						}
					}
				}
				else
				{
					//IF NO PLAYER EXISTS, CREATE ONE
					enemy = malloc(sizeof(Enemy));
					InitEnemy(enemy);
				}

        			BeginDrawing();
            			ClearBackground(PORANGE);
            			DrawTower(tower);
				DrawText(pointsText, 0, 0, 24, PDARKRED);
				if(enemy){DrawEnemy(*enemy); 
        			EndDrawing();
				
				//VERIFIES IF ENEMY TOUCHED THE TOWER AND ENDS THE GAME
				if(CheckCollisionRecs(tower.rec, enemy->rec)){free(enemy); enemy=NULL; currentScreen=TITLE; CheckAndUpdateMaxPoints();}}

			       	break;
			} 
			default: break;
		}
	}
	//CLOSE WINDOW AND FINISH THE GAME
	CloseWindow();
	return 0;
}
