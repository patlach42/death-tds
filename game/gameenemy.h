#ifndef GAMEENEMY_H
#define GAMEENEMY_H
#include "gameobject.h"
#include "gameplayer.h"

class gameEnemyType{
public:
    graphicsObject* graphics;

    void setR(float we){r=we;}
    float getR(){return r;}
    void setSpeed(float s){speed = s;}
    void setRotateSpeed(double rs){rotateSpeed = rs;}
    float getSpeed(){return speed;}
    double getRotateSpeed(){return rotateSpeed;}
private:
    double r;
    float speed;
    double rotateSpeed;
};

class gameEnemy : public gameMovingObject
{
public:

    gameEnemy(gameEnemyType* type);
    void Collision(gameObject *object);
    objectType Type(){return ENEMY_OBJECT;}
};

class enemyControls
{
public:
    static enemyControls& Instance()
    {
            static enemyControls theSingleInstance;
            return theSingleInstance;
    }
    void setPl(gamePlayer* pl){player=pl;}
    void addEnemy(gameEnemyType* en, int cx, int cy);

    void deleteEnemy(gameEnemy* en);
    int getEnemyCount(){return arrEnemy.size();}
    void checkControls();
private:
    std::vector <gameEnemy*> arrEnemy;
    gamePlayer* player;
};

#endif // GAMEENEMY_H
