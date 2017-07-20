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
#include "gameobjecttypes.h"
#include "gamefield.h"
#include "gameplayer.h"
#include "gameplayercontrols.h"
#include "gametimer.h"
#include "gameenemy.h"

using namespace std;

int main(void)
{
    SDL_Event sdlEvents;
    bool appQuit = false;
    SDL_Init(SDL_INIT_EVERYTHING);
    graphics::Instance().setWindowWidth(800);
    graphics::Instance().setWindowHeight(600);
    graphics::Instance().glInit();
    gameField* field = (gameField*) gameObjectManager::Instance().addObject(new gameField(2000,2000));
    field -> setTile("tile.png");
    field -> makeFieldTexture();
    gameWeapon* weapon1 = new gameWeapon;

    weapon1 -> bullettexture = graphics::Instance().loadTextureFromSurface(IMG_Load("bullet.png"));
    weapon1->bulletr = 9;
    weapon1->bulletspeed = 9;
    weapon1->delay = 40;

    gamePlayer* player = (gamePlayer*) gameObjectManager::Instance().addObject(new gamePlayer);
    player->setCenterX(field->graphics->getWidth()/2);
    player->setCenterY(field->graphics->getHeight()/2);
    player->setR(10);
    player->graphics->setWidth(50);
    player->graphics->setHeight(50);
    player->graphics->setTexture(graphics::Instance().loadTextureFromSurface(IMG_Load("player.png")));
    player->setSpeed(6);
    player->setRotateSpeed(M_PI/20);
    player->weapon = weapon1;
    gamePlayerControls::Instance().player = player;
    graphics::Instance().setCamera(new graphicsCamera(field->graphics->getWidth(),field->graphics->getHeight()));
    gamePlayerControls::Instance().setCamera(graphics::Instance().getCamera());

    gameEnemyType* enemytype = new gameEnemyType;
    enemytype -> graphics = new graphicsObject;
    enemytype -> graphics -> setWidth(100);
    enemytype -> graphics -> setHeight(100);
    enemytype -> graphics -> setTexture(graphics::Instance().loadTextureFromSurface(IMG_Load("enemy.png")));
    enemytype -> setSpeed(2);
    enemytype -> setR(10);
    enemytype -> setRotateSpeed(M_PI/20);

    enemyControls::Instance().setPl(player);

    gameTimer* timer = new gameTimer;

    //gamevars
    Uint64 lastEnemyGen = 0, intervalEnemyGen = 500;
    int countEnemyGen = 20;
    int maxEnemyCount = 200;

    timer->run();
    while(!appQuit){
        while(SDL_PollEvent(&sdlEvents))
        {
            switch(sdlEvents.type){
                case SDL_MOUSEMOTION:
                    break;
                case SDL_QUIT:
                    appQuit = true;
                    break;
                default:
                    //Any other
                    break;
            }
        }
        timer->update();
        if ((timer->cooldown(lastEnemyGen, intervalEnemyGen) && (enemyControls::Instance().getEnemyCount() < maxEnemyCount)))
        {
            for(int i = 0; i < countEnemyGen; i++){
                switch(rand()%4+1){
                    case 1: enemyControls::Instance().addEnemy(enemytype, rand()%2000, 0); break;
                    case 2: enemyControls::Instance().addEnemy(enemytype, 0, rand()%2000); break;
                    case 3: enemyControls::Instance().addEnemy(enemytype, 2000, rand()%2000); break;
                    case 4: enemyControls::Instance().addEnemy(enemytype, rand()%2000, 2000); break;
                }
            }
            lastEnemyGen = timer->getTicks();
        }

        if (player->health == 0) appQuit = true;
        if(SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
            if((timer->cooldown(player->lastshot, player->weapon->delay)))
                {
                    gameBulletController::Instance().addBullet(player->weapon, player->getCenterX(), player->getCenterY(),
                                                                       player->getAngle()+(rand()%3-1)*((M_PI/100)*(rand()%10)));
                    player ->lastshot = timer->getTicks();
                }
        gameBulletController::Instance().checkControls();
        gamePlayerControls::Instance().checkControls();
        enemyControls::Instance().checkControls();
        gameObjectManager::Instance().updateObjectsGraphics();
        gameObjectManager::Instance().checkCollisions();
        graphics::Instance().renderScene();
    }
    return 0;
}

