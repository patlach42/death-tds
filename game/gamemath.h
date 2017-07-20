#ifndef GAMEMATH_H
#define GAMEMATH_H

#include <cmath>
#include "sdl2/SDL.h"

class gameMath
{
public:
    static gameMath& Instance()
    {
            static gameMath Single;
            return Single;
    }
    double rotateAngle(double angle, double angleto, double step);
    double getAngle(int x1, int x2, int y1, int y2);
};

#endif // GAMEMATH_H
