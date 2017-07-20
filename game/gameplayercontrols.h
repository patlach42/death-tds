                                                    #ifndef PLAYERCONTROLS_H
#define PLAYERCONTROLS_H
#include <vector>
#include <cmath>
#include <GL/glu.h>
#include "sdl2/SDL.h"
#include "sdl2/SDL_opengl.h"
#include "sdl2/SDL_image.h"
#undef main
#include "graphics.h"
#include "gamemath.h"
#include "gameobject.h"
#include "gameplayer.h"

class gamePlayerControls
{
public:
    static gamePlayerControls& Instance()
    {
            static gamePlayerControls theSingleInstance;
            return theSingleInstance;
    }

    const Uint8 *keyboardState = SDL_GetKeyboardState(NULL);
    int mousex, mousey;
    void checkControls();
    void setCamera(graphicsCamera* cam){camera = cam;}
    graphicsCamera* getCamera(){return camera;}
    graphicsCamera* camera;
    gamePlayer* player;
};

#endif // PLAYERCONTROLS_H
