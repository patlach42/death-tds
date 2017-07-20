#include "gameweapon.h"


void gameBulletController::checkControls(){
    for(unsigned int i=0; i<arrBullet.size(); i++)
    {
        arrBullet[i]->movement();
    }
}

void gameBulletController::addBullet(gameWeapon* en, int cx, int cy, double angle)
{
    gameBullet* res = (gameBullet*)(gameObjectManager::Instance().addObject(new gameBullet()));
    res -> graphics ->setWidth(100);
    res -> graphics ->setHeight(100);
    res -> graphics ->setTexture(en->bullettexture);
    res -> setCenterX(cx);
    res -> setCenterY(cy);
    res -> setR(en->bulletr);
    res -> setSpeed(en->bulletspeed);
    res -> setMovementAngle(angle);
    res -> setAngle(angle);
    arrBullet.push_back(res);
}


void gameBulletController::deleteBullet(gameBullet* res)
{
    std::vector<gameBullet*>::iterator the_iterator;
     the_iterator = arrBullet.begin();
     while(the_iterator != arrBullet.end())
     {
         if(res==(*the_iterator)){arrBullet.erase(the_iterator); continue;}
         the_iterator++;
     }
     gameObjectManager::Instance().deleteObject(res);
}

void gameBullet::Collision(gameObject* object){

}
