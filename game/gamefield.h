#ifndef GAMEFIELD_H
#define GAMEFIELD_H
#include <GL/glu.h>
#include "sdl2/SDL.h"
#include "sdl2/SDL_opengl.h"
#include "sdl2/SDL_image.h"
#include "graphics.h"
#include "gamemath.h"
#include "gameobject.h"

class gameField : public gameObject
{
public:
    gameField(int w, int h);
    void makeFieldTexture();
    void setTile(char* path){tilepath = path;}
private:
    int fieldW, fieldH;
    char* tilepath;
};

#endif // GAMEFIELD_H
