#ifndef POINTS_H
#define POINTS_H

#include <stdio.h>
#include "screens/screens.h"
#include "color_palette/color_palette.h"

extern int points;
extern int maxPoints;
extern char pointsText[32];
extern char maxPointsText[32];

void InitPoints(void);
void UpdatePointsText(void);
void CheckAndUpdateMaxPoints(void);
void UpdateMaxPointsText(void);
void IncreasePoints(int amount);
void DecreasePoints(int amount);
void DrawPoints(Vector2 Pos);

#endif
