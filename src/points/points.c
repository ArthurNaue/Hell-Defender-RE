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

void CheckAndUpdateMaxPoints(void) 
{
    if(points > maxPoints){maxPoints = points; points = 0;}
}

void UpdateMaxPointsText(void)
{
	sprintf(maxPointsText, "Max Score: %d", maxPoints);
}
