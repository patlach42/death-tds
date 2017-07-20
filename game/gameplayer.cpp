#include "gameplayer.h"

gamePlayer::gamePlayer()
{
}
void gamePlayer::Collision(gameObject* object)
{
    if(object->Type()==ENEMY_OBJECT)
    {
        this->health=0;
    }
}
