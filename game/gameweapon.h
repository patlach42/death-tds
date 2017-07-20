#ifndef GAMEWEAPON_H
#define GAMEWEAPON_H
#include "gameobject.h"

class gameWeapon
{
public:
    int delay, reloadDelay, bulletscount, bulletspeed, bulletr, damage;
    GLuint bullettexture;
};

class gameBullet : public gameMovingObject
{
public:
    int damage;
    GLuint bullettexture;
    virtual void Collision(gameObject* object);
    objectType Type(){return BULLET_OBJECT;}
};

class gameBulletController
{
public:
    static gameBulletController& Instance()
    {
            static gameBulletController theSingleInstance;
            return theSingleInstance;
    }
    void addBullet(gameWeapon* en, int cx, int cy, double angle);
    void checkControls();
    void deleteBullet(gameBullet* res);
    private:
        std::vector <gameBullet*> arrBullet;
};

#endif // GAMEWEAPON_H
