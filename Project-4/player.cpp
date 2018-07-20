#include "player.h"

Player::Player( const std::string& name) :
  twowaySprite(name),
  collision(false),
  initialVelocity(getVelocity()),
  facing(RIGHT)
{ }

Player::Player(const Player& s) :
  twowaySprite(s), 
  collision(s.collision),
  initialVelocity(s.getVelocity()),
  facing(s.facing)
  { }

Player& Player::operator=(const Player& s) {
  twowaySprite::operator=(s);
  collision = s.collision;
  initialVelocity = s.initialVelocity;
  facing = s.facing;
  return *this;
}

void Player::stop() { 
  setVelocity(Vector2f(0,0));
}

void Player::right() { 
  if ( getX() < worldWidth-getScaledWidth()) {
    setVelocityX(initialVelocity[0]);
    twowaySprite::images = twowaySprite::imagesRight;
    facing = RIGHT;
  }
} 
void Player::left()  { 
  if ( getX() > 0) {
    setVelocityX(-initialVelocity[0]);
    twowaySprite::images = twowaySprite::imagesLeft;
    facing = LEFT;
  }
} 
void Player::up()    { 
  if ( getY() > 0) {
    setVelocityY( -initialVelocity[1] );
  }
} 
void Player::down()  { 
  if ( getY() < worldHeight-getScaledHeight()) {
    setVelocityY( initialVelocity[1] );
  }
}

void Player::update(Uint32 ticks) {
    advanceFrame(ticks);
    twowaySprite::update(ticks);

    Vector2f incr = getVelocity() * static_cast<float>(ticks) * 0.001;
    setPosition(getPosition() + incr);
    stop();
}

