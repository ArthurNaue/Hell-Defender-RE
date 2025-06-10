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

	InitTower(&tower);	
	InitTowerAttack(&towerAttack);

	//INITIALIZE THE VARIABLE THAT CONTROLS THE GAME
	int game = 1;

	while (game==1)
	{
		//UPDATES THE DELTA TIME
		UpdateDt();

		//VERIFIES CURRENT SCREEN
		switch(currentScreen)
		{
			case TITLE:
			{
				UpdateMaxPointsText();

				BeginDrawing();

            			ClearBackground(PORANGE);

				DrawTextureV(tittleLetteringTex, (Vector2){0 + 48, 100}, WHITE);

				DrawText(maxPointsText, 0, 0, 24, PDARKRED);
				
				if(GuiButton((Rectangle){SCREEN_WIDTH/2 - 100, SCREEN_HEIGHT/2 + 50, 200, 100}, "PLAY")){GameplayScreen();}
				if(GuiButton((Rectangle){SCREEN_WIDTH/2 - 100, SCREEN_HEIGHT/2 + 150, 200, 100}, "EXIT")){game = 0;}

        			EndDrawing();

				break;
			}
			case GAMEPLAY:
			{
				CreateFireDecoration();

				CreateEnemy();
				MoveEnemies();

				if(IsKeyPressed(KEY_ESCAPE))
				{
					DeleteFireDecorations();
					DeleteEnemies();
					CheckAndUpdateMaxPoints();
					TitleScreen();
				}

				UpdatePointsText();

				BeginDrawing();

            			ClearBackground(PORANGE);

       				DrawFireDecorations();

				DrawTower(tower);
				UpdateTowerAttack(&towerAttack);
				
				DrawEnemies();

				DrawText(pointsText, 0, 0, 24, PDARKRED);

				EndDrawing();
			
			       	break;
			} 
			default: break;
		}
	}

	//CLOSE WINDOW AND FINISH THE GAME
	CloseWindow();
	return 0;
}
