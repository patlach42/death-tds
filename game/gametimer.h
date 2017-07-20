#ifndef GAMETIMER_H
#define GAMETIMER_H
#include "sdl2/SDL.h"

class gameTimer{
public:
    void update(){if(!paused) ticks = SDL_GetTicks()-pausedTicks; else pausedTicks = SDL_GetTicks()-ticks;}
    Uint64 getTicks(){return ticks;}
    void run(){if(paused){update(); paused=false;}}
    void pause(){paused=true;}

    bool cooldown(Uint64 lastuse, unsigned int interval){return (ticks - lastuse>interval) ? true : false;}
private:
    Uint64 ticks, pausedTicks;
    bool paused=true;
};


class game{
public:

private:
    gameTimer* timer;
};

#endif // GAMETIMER_H
