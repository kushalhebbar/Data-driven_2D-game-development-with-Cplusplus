#include <iostream>
#include <cmath>
#include "bullet.h"

void Bullet::update(Uint32 ticks) { 
  Vector2f pos = getPosition();
  int worldwidth = Gamedata::getInstance().getXmlInt("world/width");
  Sprite::update(ticks);
  distance += ( hypot(getX()-pos[0], getY()-pos[1]) );
  if (distance > maxDistance || getX()<0 || getX()>worldwidth-50) tooFar = true;
}

