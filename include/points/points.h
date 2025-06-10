#ifndef POINTS_H
#define POINTS_H

#include <stdio.h>

extern int points;
extern int maxPoints;
extern char pointsText[32];
extern char maxPointsText[32];

void InitPoints(void);
void UpdatePointsText(void);
void CheckAndUpdateMaxPoints(void);
void UpdateMaxPointsText(void);

#endif
