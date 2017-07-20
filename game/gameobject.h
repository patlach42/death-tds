#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include <cmath>
#include "graphics.h"
#include "gamemath.h"
#include "gameobjecttypes.h"
//makingofsimpleobj
//gameObject* obj = gameObjectManager::Instance().addObject(new gameObject);
//obj -> graphics -> setTexture(graphics::Instance().loadTextureFromSurface(IMG_Load("tile.png")));
//obj -> graphics -> setHeight(100);
//obj -> graphics -> setWidth(100);
class gameObject{
public:
    graphicsObject* graphics = NULL;
    void setCenterX(float x){cx=x;}
    void setCenterY(float y){cy=y;}
    void setR(float we){r=we;}
    float getR(){return r;}
    void setAngle(double a){angle=a;}
    float getCenterX(){return cx;}
    float getCenterY(){return cy;}

    double getAngle(){return angle;}
    virtual void Collision(gameObject* object){}
    virtual objectType Type(){return EMPTY_OBJECT;}
private:
    float cx, cy, r;
    double angle;
};

class gameMovingObject : public gameObject
{
public:
      void setSpeed(float s){speed = s;}
      void setRotateSpeed(double rs){rotateSpeed = rs;}
      float getSpeed(){return speed;}
      double getRotateSpeed(){return rotateSpeed;}

      void setMovementAngle(double ma){movementAngle = ma;}
      void setRotateToAngle(double mta){
          if(abs(mta+2*M_PI-movementAngle) < abs(mta-movementAngle))
            rotateToAngle = mta+2*M_PI;
          else
              if(abs(mta-2*M_PI-movementAngle) < abs(mta-movementAngle))
                rotateToAngle = mta-2*M_PI;
              else
                rotateToAngle = mta;

      }
      double getMovementAngle(){return movementAngle;}
      double getRotateToAngle(){return rotateToAngle;}

      void movement() {
          setMovementAngle(gameMath::Instance().rotateAngle(movementAngle, rotateToAngle, rotateSpeed));
          double stepX = getCenterX() + cos(getMovementAngle()) * getSpeed(),
                 stepY = getCenterY() + sin(getMovementAngle()) * getSpeed();
          if (((stepX >= 0) && (stepX <= 2000) && (stepY >= 0) && (stepY <= 2000)) || (Type() != PLAYER_OBJECT))
          {
              setCenterX(stepX);
              setCenterY(stepY);
          }
       }
private:
    float speed;
    double movementAngle, rotateToAngle, rotateSpeed;
};

class gameObjectManager{
public:
    static gameObjectManager& Instance()
    {
            static gameObjectManager theSingleInstance;
            return theSingleInstance;
    }
    gameObject* addObject(gameObject* object);
    void deleteObject(gameObject* object);
    void updateObjectsGraphics();
    void checkCollisions();
private:
    std::vector <gameObject*> gameObjects;
};
#endif // GAMEOBJECT_H
