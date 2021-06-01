#ifndef TMUTILITY_H
#define TMUTILITY_H

#include<math.h>
enum Mode{DRAWING,SELECTION,MULTIPLE_SELECTION,NONE};
enum Component{LINE,RECTANGLE,FREE_HAND_TOOL,CIRCLE};
class TMUtility
{
public:
    TMUtility();
    static double distanceBetweenTwoPoints(double x1, double y1, double x2, double y2);
};

#endif // TMUTILITY_H
