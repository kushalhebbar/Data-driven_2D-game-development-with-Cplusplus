#ifndef PLAYER__H
#define PLAYER__H

#include "twowaysprite.h"

class Player : public twowaySprite {
public:
  Player(const std::string&);
  Player(const Player&);
  virtual void update(Uint32 ticks);

  void collided() { collision = true; }
  void missed() { collision = false; }
  Player& operator=(const Player&);

  void right();
  void left();
  void up();
  void down();
  void stop();

  enum FACE {LEFT, RIGHT};
  FACE getPlayerDirection() const { return facing; }
private:
  bool collision;
  Vector2f initialVelocity;
  FACE facing;
};
#endif
