#include "gamemath.h"

double gameMath::rotateAngle(double angle, double angleto, double step)
{
    double a=angle;
    if (a>2*M_PI) a-=2*M_PI;
    if (a<0) a+=2*M_PI;

    if (((a+step)>angleto)&&((a-step)<angleto)) a=angleto;
            else
    {
    if (a<angleto)
        a+=step;
    else
        a-=step;
    }
    return a;
}

double gameMath::getAngle(int x1, int y1, int x2, int y2){

    if(y1<y2)
    {
        if(x1<x2)
        return asin(abs(y1-y2)/sqrt(abs(x1-x2)*abs(x1-x2)+abs(y1-y2)*abs(y1-y2)));
        else
        return M_PI+asin(-abs(y1-y2)/sqrt(abs(x1-x2)*abs(x1-x2)+abs(y1-y2)*abs(y1-y2)));
    }

    else
    {
            if(x1<x2)
            return asin(-abs(y1-y2)/sqrt(abs(x1-x2)*abs(x1-x2)+abs(y1-y2)*abs(y1-y2)));
            else
            return M_PI+asin(abs(y1-y2)/sqrt(abs(x1-x2)*abs(x1-x2)+abs(y1-y2)*abs(y1-y2)));
    }

return 0;
}
