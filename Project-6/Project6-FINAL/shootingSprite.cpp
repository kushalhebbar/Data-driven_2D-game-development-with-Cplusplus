#include "shootingSprite.h"
#include "gamedata.h"

ShootingSprite::ShootingSprite(const std::string& name) :
  SubjectSprite(name),
  bulletName( Gamedata::getInstance().getXmlStr(name+"/bullet") ),
  bullets(),
  freelist(),
  minSpeed( Gamedata::getInstance().getXmlInt(bulletName+"/speedX") ),
  bulletInterval(Gamedata::getInstance().getXmlInt(bulletName+"/interval")),
  timeSinceLastFrame(0)
{ }

ShootingSprite::ShootingSprite(const ShootingSprite& s) :
  SubjectSprite(s),
  bulletName(s.bulletName),
  bullets(s.bullets),
  freelist(s.freelist),
  minSpeed(s.minSpeed),
  bulletInterval(s.bulletInterval),
  timeSinceLastFrame(s.timeSinceLastFrame)
{ }

unsigned int ShootingSprite::getBulletList(){
  return bullets.size();
}

unsigned int ShootingSprite::getFreeList(){
  return freelist.size();
}

void ShootingSprite::shoot() { 
  if ( timeSinceLastFrame < bulletInterval ) return;
  float deltaX = getScaledWidth() - 50;
  float deltaY = getScaledHeight()/4;

  if(getPlayerDirection() == RIGHT){
    if(freelist.empty()) {
      Bullet bullet(bulletName);
      bullet.setPosition( getPosition() + Vector2f(deltaX, deltaY) );
      bullet.setVelocity( getVelocity() + Vector2f(minSpeed, 40) );
      bullets.push_back( bullet );
      timeSinceLastFrame = 0;
    } else{
      Bullet b=freelist.front();
      freelist.pop_front();
      b.reset();
      b.setPosition( getPosition() + Vector2f(deltaX, deltaY) );
      b.setVelocity( getVelocity() + Vector2f(minSpeed, 0) );
      bullets.push_back(b);
    }
  } else{
    deltaX = deltaX - 175;
    if(freelist.empty()) {
      Bullet bullet(bulletName);
      bullet.setPosition( getPosition() + Vector2f(deltaX, deltaY) );
      bullet.setVelocity( getVelocity() - Vector2f(minSpeed, 0) );
      bullets.push_back( bullet );
      timeSinceLastFrame = 0;
    } else{
      Bullet b=freelist.front();
      freelist.pop_front();
      b.reset();
      b.setPosition( getPosition() + Vector2f(deltaX, deltaY) );
      b.setVelocity( getVelocity() - Vector2f(minSpeed, 0) );
      bullets.push_back(b);
    }
  }

  
}

void ShootingSprite::draw() const { 
  SubjectSprite::draw();
  for ( const Bullet& bullet : bullets ) {
    bullet.draw();
  }
}

void ShootingSprite::update(Uint32 ticks) {
  timeSinceLastFrame += ticks;
  SubjectSprite::update(ticks);
  std::list<Bullet>::iterator ptr=bullets.begin();
  while(ptr!=bullets.end())
  {
    ptr->update(ticks);
    if(ptr->goneTooFar()){
      freelist.push_back(*ptr);
      ptr=bullets.erase(ptr);
    }
    else ++ptr;
  }
}

