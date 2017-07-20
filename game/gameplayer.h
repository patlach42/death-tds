#ifndef GAMEPLAYER_H
#define GAMEPLAYER_H
#include "gameobject.h"
#include "gameweapon.h"


class gamePlayer : public gameMovingObject
{
public:
    gamePlayer();
    gameWeapon* weapon;
    int bullets, health = 100;
    Uint64 lastshot;
    Uint64 lastreload;

    objectType Type(){return PLAYER_OBJECT;}
    void Collision(gameObject* object);
};

#endif // GAMEPLAYER_H
