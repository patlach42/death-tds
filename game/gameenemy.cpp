#include "gameenemy.h"

gameEnemy::gameEnemy(gameEnemyType* type)
{

    setR(type->getR());
    setSpeed(type->getSpeed());
    setRotateSpeed(type->getRotateSpeed());
    graphics = new graphicsObject;
    graphics -> setTexture(type -> graphics ->getTexture());
    graphics -> setWidth(type -> graphics ->getWidth());
    graphics -> setHeight(type -> graphics ->getHeight());
}

void gameEnemy::Collision(gameObject *object){
    if(object->Type()==BULLET_OBJECT){
        enemyControls::Instance().deleteEnemy(this);
        gameBulletController::Instance().deleteBullet((gameBullet*) object);
        return;
    }

}

void enemyControls::checkControls(){
    for(int i=0; i<arrEnemy.size(); i++)
    {
        arrEnemy[i]->setRotateToAngle( gameMath::Instance().getAngle(arrEnemy[i]->getCenterX(),arrEnemy[i]->getCenterY(),
                                                                       player->getCenterX(),player->getCenterY()));
        arrEnemy[i]->movement();
        arrEnemy[i]->setAngle(arrEnemy[i]->getRotateToAngle());
    }
}

void enemyControls::addEnemy(gameEnemyType* en, int cx, int cy)
{
    gameEnemy* res = (gameEnemy*)(gameObjectManager::Instance().addObject(new gameEnemy(en)));
    res -> setCenterX(cx);
    res -> setCenterY(cy);
    arrEnemy.push_back(res);
}

void enemyControls::deleteEnemy(gameEnemy* en)
{
    std::vector<gameEnemy*>::iterator the_iterator;
    the_iterator = arrEnemy.begin();
    while(the_iterator != arrEnemy.end())
    {
        if(en==(*the_iterator)){arrEnemy.erase(the_iterator); continue;}
        the_iterator++;
    }
    gameObjectManager::Instance().deleteObject(en);
}
