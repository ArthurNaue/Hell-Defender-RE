#ifndef POINTS_H
#define POINTS_H

extern int points;
extern int maxPoints;
extern char pointsText[32];
extern char maxPointsText[32];

void InitPoints(void);
void CheckAndUpdateMaxPoints(void);

#endif
