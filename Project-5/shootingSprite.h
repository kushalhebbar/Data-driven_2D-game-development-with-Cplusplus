#ifndef SHOOTINGSPRITE__H
#define SHOOTINGSPRITE__H
#include <string>
#include <iostream>
#include <list>
#include "sprite.h"
#include "bullet.h"
#include "subjectSprite.h"

class ShootingSprite : public SubjectSprite {
public:
  ShootingSprite(const std::string& n);
  ShootingSprite(const ShootingSprite& s);

  virtual void update(Uint32 ticks);
  virtual void draw() const;

  std::list<Bullet> getBullets() {return bullets;};
  unsigned int getBulletList();
  unsigned int getFreeList();

  void shoot();

private:
  std::string bulletName;
  std::list<Bullet> bullets;
  std::list<Bullet> freelist;
  float minSpeed;
  float bulletInterval;
  float timeSinceLastFrame;
  ShootingSprite& operator=(const ShootingSprite&);
};

#endif