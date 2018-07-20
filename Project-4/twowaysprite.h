#ifndef TWOWAYSPRITE__H
#define TWOWAYSPRITE__H
#include <string>
#include <vector>
#include <cmath>
#include "drawable.h"

class ExplodingSprite;

class twowaySprite : public Drawable {
public:
  twowaySprite(const std::string&);
  twowaySprite(const twowaySprite&);
  ~twowaySprite();
  virtual void draw() const;
  virtual void update(Uint32 ticks);

  virtual const Image* getImage() const { 
    return images[currentFrame]; 
  }
  virtual const SDL_Surface* getSurface() const { 
    return images[currentFrame]->getSurface();
  }
  int getScaledWidth()  const { 
    return getScale()*images[currentFrame]->getWidth(); 
  } 
  int getScaledHeight()  const { 
    return getScale()*images[currentFrame]->getHeight(); 
  } 
  virtual void explode();

protected:
  std::vector<Image *> imagesRight;
  std::vector<Image *> imagesLeft;
  std::vector<Image *> images;
  
  ExplodingSprite* explosion;
  unsigned currentFrame;
  unsigned numberOfFrames;
  unsigned frameInterval;
  float timeSinceLastFrame;
  int worldWidth;
  int worldHeight;

  void advanceFrame(Uint32 ticks);
  twowaySprite& operator=(const twowaySprite&);
  Vector2f makeVelocity(int, int) const;
};
#endif
