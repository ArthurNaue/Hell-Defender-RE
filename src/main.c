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
#include "letterings/letterings.h"
#include "tower/tower.h"
#include "tower/tower_attack/tower_attack.h"
#include "enemy/enemy.h"
#include "fire_decorations/fire_decorations.h"

int main(void)
{
	StartWindow();

	//RANDOMIZE RANDOM SEED
	srand(time(NULL));

	//INITIALIZE THE POINTS
	InitPoints();

	InitLettering(&titleLettering, LoadImage("assets/images/letterings/title_lettering.png"));

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

				DrawText(maxPointsText, 0, 0, 24, PDARKRED);
	
				DrawLettering(titleLettering.tex, (Vector2){48, 100});

				GuiSetStyle(BUTTON, BASE_COLOR_NORMAL, 0x7A1C4BFF);
				GuiSetStyle(BUTTON, BORDER_COLOR_NORMAL, 0x1B0326FF);
				GuiSetStyle(BUTTON, TEXT_COLOR_NORMAL, 0x1B0326FF);
				GuiSetStyle(BUTTON, BASE_COLOR_FOCUSED, 0x1B0326FF);
				GuiSetStyle(BUTTON, BORDER_COLOR_FOCUSED, 0x1B0326FF);
				GuiSetStyle(BUTTON, TEXT_COLOR_FOCUSED, 0xEFF9D6FF);
				GuiSetStyle(BUTTON, BASE_COLOR_PRESSED, 0xEFF9D6FF);
				GuiSetStyle(BUTTON, BORDER_COLOR_PRESSED, 0x1B0326FF);
				GuiSetStyle(BUTTON, TEXT_COLOR_PRESSED, 0x1B0326FF);

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
				
				DrawEnemies();

				UpdateTowerAttack(&towerAttack);

				DrawText(pointsText, 0, 0, 24, PDARKRED);

				EndDrawing();
			
				break;
			} 
			default: break;
		}
	}

	UnloadLetteringTex(&titleLettering.tex);

	//CLOSE WINDOW AND FINISH THE GAME
	CloseWindow();
	return 0;
}
