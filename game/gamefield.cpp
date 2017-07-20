#include "gamefield.h"

gameField::gameField(int w, int h)
{
    fieldW=w;
    fieldH=h;
    setCenterX(w/2);
    setCenterY(h/2);
}

void gameField::makeFieldTexture()
{
    graphics -> setWidth(fieldW);
    graphics -> setHeight(fieldH);
    SDL_Surface *surface;

    Uint32 rmask, gmask, bmask, amask;
    #if SDL_BYTEORDER == SDL_BIG_ENDIAN
        rmask = 0xff000000;
        gmask = 0x00ff0000;
        bmask = 0x0000ff00;
        amask = 0x000000ff;
    #else
        rmask = 0x000000ff;
        gmask = 0x0000ff00;
        bmask = 0x00ff0000;
        amask = 0xff000000;
    #endif

    surface = SDL_CreateRGBSurface(0, graphics -> getWidth(), graphics -> getHeight(), 24, rmask, gmask, bmask, amask);
    SDL_SetSurfaceBlendMode(surface, SDL_BLENDMODE_BLEND);
    SDL_Surface* tile = IMG_Load(tilepath);
    int tileWidth=tile->w, tileHeight=tile->h;
    SDL_Rect dstrect;
    for(int i=0; i<graphics -> getHeight()/tileHeight+1; i++)
        for(int j=0; j<graphics -> getWidth()/tileWidth+1; j++)
        {
            dstrect.x=j*tileWidth;
            dstrect.y=i*tileHeight;
            dstrect.w=tileWidth;
            dstrect.h=tileHeight;

            SDL_UpperBlit(tile,NULL,surface,&dstrect);
        }

    graphics -> setTexture(graphics::Instance().loadTextureFromSurface(surface));

    SDL_FreeSurface(tile);
    SDL_FreeSurface(surface);
}
