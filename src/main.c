#include <time.h>
#include "raylib.h"
#include "window_config/window_config.h"
#include "color_palette/color_palette.h"
#include "points/points.h"
#include "screens/screens.h"
#include "dt/dt.h"
#include "animated_sprite/animated_sprite.h"
#include "letterings/letterings.h"
#include "buttons/buttons.h"
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

	while (game==1)
	{
		//UPDATES THE DELTA TIME
		UpdateDt();

		//VERIFIES CURRENT SCREEN
		switch(currentScreen)
		{
			case TITLE:
			{
				ShowCursor();

				CreateFireDecoration();

				BeginDrawing();

				ClearBackground(PORANGE);

				DrawFireDecorations();
	
				DrawLettering(titleLettering.tex, (Vector2){48, 100});
	
				InitButtonStyle();

				DrawTitleScreenButtons();

				DrawPoints((Vector2){5, 5});

				EndDrawing();

				break;
			}
			case GAMEPLAY:
			{
				DeleteFireDecorations();

				CreateBoss(&boss);
				MoveBoss(&boss);

				CreateEnemy();
				MoveEnemies();

				if(IsKeyPressed(KEY_ESCAPE))
				{
					DeleteEnemies();
					CheckAndUpdateMaxPoints();
					TitleScreen();
				}

				BeginDrawing();

				ClearBackground(PORANGE);

				DrawTower(tower);
				
				DrawEnemies();
				DrawBoss(boss);

				UpdateTowerAttack(&towerAttack);

				DrawPoints((Vector2){5, 5});

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
