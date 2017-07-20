#include "gameobject.h"

gameObject* gameObjectManager::addObject(gameObject* object){
    if(object->graphics==NULL) object->graphics = new graphicsObject;
    graphics::Instance().addObjectToScene(object->graphics);
    gameObjects.push_back(object);
    return object;
}

void gameObjectManager::deleteObject(gameObject* en){
    std::vector<gameObject*>::iterator the_iterator;
    the_iterator = gameObjects.begin();
    while(the_iterator != gameObjects.end())
    {
        if(en==(*the_iterator)){gameObjects.erase(the_iterator); continue;}
        the_iterator++;
    }
    graphics::Instance().deleteObjFromScene(en->graphics);
    free(en->graphics);
    free(en);
}

void gameObjectManager::updateObjectsGraphics(){


    std::vector<gameObject*>::iterator the_iterator;
    the_iterator = gameObjects.begin();
    while(the_iterator != gameObjects.end())
    {
        (*the_iterator)->graphics->setX((*the_iterator)->getCenterX()-(*the_iterator)->graphics->getWidth()/2);
        (*the_iterator)->graphics->setY((*the_iterator)->getCenterY()-(*the_iterator)->graphics->getHeight()/2);
        (*the_iterator)->graphics->setAngle((*the_iterator)->getAngle());
        the_iterator++;
    }

}


void gameObjectManager::checkCollisions(){
    int x1,x2,y1,y2;
    for(unsigned int i=0; i<gameObjects.size(); i++)
    {
        x1=gameObjects[i]->getCenterX();
        y1=gameObjects[i]->getCenterY();
        for(unsigned int j=i+1; j<gameObjects.size(); j++)
        {
            x2=gameObjects[j]->getCenterX();
            y2=gameObjects[j]->getCenterY();
            if ((sqrt(abs(x1-x2) * abs(x1-x2) + abs(y1-y2) * abs(y1-y2))) < gameObjects[i]->getR() + gameObjects[j]->getR())
            {
                gameObjects[j]->Collision(gameObjects[i]);
                gameObjects[i]->Collision(gameObjects[j]);
            }
        }
    }
}
