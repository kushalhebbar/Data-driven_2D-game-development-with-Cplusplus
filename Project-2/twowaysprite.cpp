#include "twowaysprite.h"
#include "gamedata.h"
#include "renderContext.h"

void twowaySprite::advanceFrame(Uint32 ticks) {
	timeSinceLastFrame += ticks;
	if (timeSinceLastFrame > frameInterval) {
    currentFrame = (currentFrame+1) % numberOfFrames;
		timeSinceLastFrame = 0;
	}
}

Vector2f twowaySprite::makeVelocity(int vx, int vy) const {
	float a = Gamedata::getInstance().getRandInRange(vx-70, vx+70);
	float b = Gamedata::getInstance().getRandInRange(vy, vy);
  	vx += a;
  	vy += b;
  
  return Vector2f(a, b);
}
twowaySprite::twowaySprite( const std::string& name) :
  Drawable(name, 
           Vector2f(Gamedata::getInstance().getXmlInt(name+"/startLoc/x"), 
                    Gamedata::getInstance().getXmlInt(name+"/startLoc/y")), 
           makeVelocity(Gamedata::getInstance().getXmlInt(name+"/speedX"),
                    Gamedata::getInstance().getXmlInt(name+"/speedY"))
           ),
  imagesRight( RenderContext::getInstance()->getImages(name) ),
  imagesLeft( RenderContext::getInstance()->getImages(name+"Left") ),
  images( RenderContext::getInstance()->getImages(name) ),

  currentFrame(0),
  numberOfFrames( Gamedata::getInstance().getXmlInt(name+"/frames") ),
  frameInterval( Gamedata::getInstance().getXmlInt(name+"/frameInterval")),
  timeSinceLastFrame( 0 ),
  worldWidth(Gamedata::getInstance().getXmlInt("world/width")),
  worldHeight(Gamedata::getInstance().getXmlInt("world/height"))
{ }

twowaySprite::twowaySprite(const twowaySprite& rhs) :
  Drawable(rhs), 
  imagesRight(rhs.imagesRight),
  imagesLeft(rhs.imagesLeft),
  images(rhs.images),
  currentFrame(rhs.currentFrame),
  numberOfFrames( rhs.numberOfFrames ),
  frameInterval( rhs.frameInterval ),
  timeSinceLastFrame( rhs.timeSinceLastFrame ),
  worldWidth( rhs.worldWidth ),
  worldHeight( rhs.worldHeight )
  { }

twowaySprite& twowaySprite::operator=(const twowaySprite& rhs) {
  Drawable::operator=(rhs);
  imagesRight = (rhs.imagesRight);
  imagesLeft = (rhs.imagesLeft);
  images = (rhs.images);
  currentFrame = (rhs.currentFrame);
  numberOfFrames = ( rhs.numberOfFrames );
  frameInterval = ( rhs.frameInterval );
  timeSinceLastFrame = ( rhs.timeSinceLastFrame );
  worldWidth = ( rhs.worldWidth );
  worldHeight = ( rhs.worldHeight );
  return *this;
}

void twowaySprite::draw() const { 
  images[currentFrame]->draw(getX(), getY(), getScale());
}

void twowaySprite::update(Uint32 ticks) { 
  advanceFrame(ticks);

  Vector2f incr = getVelocity() * static_cast<float>(ticks) * 0.001;
  setPosition(getPosition() + incr);

  if ( getY() < 0) {
      setVelocityY(std::abs(getVelocityY()));
    //setVelocityY( fabs( getVelocityY() ) );
  }
  if ( getY() > worldHeight-getScaledHeight()) {
	setVelocityY(std::abs(getVelocityY()));
	//setVelocityY( -fabs( getVelocityY() ) );
  }

  if ( getX() < 0) {
	setVelocityX( std::abs( getVelocityX() ) );
    //setVelocityX( fabs( getVelocityX() ) );
    images = imagesRight;
  }
  if ( getX() > worldWidth-getScaledWidth()) {
	setVelocityX( -std::abs( getVelocityX() ) );    
	//setVelocityX( -fabs( getVelocityX() ) );
    images = imagesLeft;
  }  

}
