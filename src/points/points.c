#include "points/points.h"

int points = 0;
int maxPoints = 0;
char pointsText[32];
char maxPointsText[32];

void InitPoints(void)
{
	points=0;
	maxPoints=0;
}

void UpdatePointsText(void)
{
	sprintf(pointsText, "Score: %d", points);
}

void UpdateMaxPointsText(void)
{
	sprintf(maxPointsText, "Max Score: %d", maxPoints);
}

void CheckAndUpdateMaxPoints(void) 
{
    if(points > maxPoints){maxPoints = points; DecreasePoints(points);}
}

void IncreasePoints(int amount)
{
	points += amount;
}

void DecreasePoints(int amount)
{
	points -= amount;
}

void DrawPoints(Vector2 pos)
{
	UpdatePointsText();
	UpdateMaxPointsText();

	if(currentScreen==TITLE)
	{
		DrawRectangle(pos.x, pos.y, 216, 26, PRED);
		DrawRectangleLines(pos.x, pos.y, 216, 26, PDARKRED);
		DrawText(maxPointsText, pos.x + 24, pos.y + 1, 24, PDARKRED);
	}
	else
	{
		DrawRectangle(pos.x, pos.y, 216, 26, PRED);
		DrawRectangleLines(pos.x, pos.y, 216, 26, PDARKRED);
		DrawText(pointsText, pos.x + 24, pos.y + 1, 24, PDARKRED);
	}
}
