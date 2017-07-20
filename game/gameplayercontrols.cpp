#include "gameplayercontrols.h"


void gamePlayerControls::checkControls(){
    SDL_GetMouseState(&mousex, &mousey);
    if (keyboardState[SDL_SCANCODE_W]&&!keyboardState[SDL_SCANCODE_A]&&!keyboardState[SDL_SCANCODE_S]&&!keyboardState[SDL_SCANCODE_D])
    {
        player->setRotateToAngle(M_PI/2);
    }
    if (!keyboardState[SDL_SCANCODE_W]&&keyboardState[SDL_SCANCODE_A]&&!keyboardState[SDL_SCANCODE_S]&&!keyboardState[SDL_SCANCODE_D])
    {
        player->setRotateToAngle(M_PI);
    }
    if (!keyboardState[SDL_SCANCODE_W]&&!keyboardState[SDL_SCANCODE_A]&&keyboardState[SDL_SCANCODE_S]&&!keyboardState[SDL_SCANCODE_D])
    {
        player->setRotateToAngle(M_PI+M_PI/2);
    }
    if (!keyboardState[SDL_SCANCODE_W]&&!keyboardState[SDL_SCANCODE_A]&&!keyboardState[SDL_SCANCODE_S]&&keyboardState[SDL_SCANCODE_D])
    {
        player->setRotateToAngle(0);
    }
    if (keyboardState[SDL_SCANCODE_W]&&!keyboardState[SDL_SCANCODE_A]&&!keyboardState[SDL_SCANCODE_S]&&keyboardState[SDL_SCANCODE_D])
    {
        player->setRotateToAngle(M_PI/4);
    }
    if (keyboardState[SDL_SCANCODE_W]&&keyboardState[SDL_SCANCODE_A]&&!keyboardState[SDL_SCANCODE_S]&&!keyboardState[SDL_SCANCODE_D])
    {
        player->setRotateToAngle(M_PI-M_PI/4);
    }
    if (!keyboardState[SDL_SCANCODE_W]&&keyboardState[SDL_SCANCODE_A]&&keyboardState[SDL_SCANCODE_S]&&!keyboardState[SDL_SCANCODE_D])
    {
        player->setRotateToAngle(M_PI + M_PI/4);
    }
    if (!keyboardState[SDL_SCANCODE_W]&&!keyboardState[SDL_SCANCODE_A]&&keyboardState[SDL_SCANCODE_S]&&keyboardState[SDL_SCANCODE_D])
    {
        player->setRotateToAngle( M_PI + M_PI/2 + M_PI/4);
    }
    if (keyboardState[SDL_SCANCODE_W]||keyboardState[SDL_SCANCODE_A]||keyboardState[SDL_SCANCODE_S]||keyboardState[SDL_SCANCODE_D])
    {
        player->movement();
    }
    player->setAngle( gameMath::Instance().getAngle(player->getCenterX()-graphics::Instance().getCamera()->getX(),
                                                      player->getCenterY()-graphics::Instance().getCamera()->getY(),
                                                      mousex, graphics::Instance().getCamera()->getHeight()-mousey));

    camera->setX(player->getCenterX()-graphics::Instance().getCamera()->getWidth()/2);
    camera->setY(player->getCenterY()-graphics::Instance().getCamera()->getHeight()/2);

}
