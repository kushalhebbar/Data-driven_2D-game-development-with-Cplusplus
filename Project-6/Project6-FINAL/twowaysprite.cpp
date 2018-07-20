#include "twowaysprite.h"
#include "gamedata.h"
#include "renderContext.h"
#include "explodingSprite.h"

void twowaySprite::advanceFrame(Uint32 ticks) {
	timeSinceLastFrame += ticks;
	if (timeSinceLastFrame > frameInterval) {
    currentFrame = (currentFrame+1) % numberOfFrames;
		timeSinceLastFrame = 0;
	}
}

twowaySprite::~twowaySprite( ) { if (explosion) delete explosion; }

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
  explosion(nullptr),
  explosionChecker(false),
  currentFrame(0),
  numberOfFrames( Gamedata::getInstance().getXmlInt(name+"/frames") ),
  frameInterval( Gamedata::getInstance().getXmlInt(name+"/frameInterval")),
  timeSinceLastFrame( 0 ),
  worldWidth(Gamedata::getInstance().getXmlInt("world/width")),
  worldHeight(Gamedata::getInstance().getXmlInt("world/height"))
{ }

twowaySprite::twowaySprite(const twowaySprite& s) :
  Drawable(s), 
  imagesRight(s.imagesRight),
  imagesLeft(s.imagesLeft),
  images(s.images),
  explosion(s.explosion),
  explosionChecker(s.explosionChecker),
  currentFrame(s.currentFrame),
  numberOfFrames( s.numberOfFrames ),
  frameInterval( s.frameInterval ),
  timeSinceLastFrame( s.timeSinceLastFrame ),
  worldWidth( s.worldWidth ),
  worldHeight( s.worldHeight )
  { }

twowaySprite& twowaySprite::operator=(const twowaySprite& s) {
  Drawable::operator=(s);
  imagesRight = (s.imagesRight);
  imagesLeft = (s.imagesLeft);
  images = (s.images);
  explosion = s.explosion;
  explosionChecker = s.explosionChecker;
  currentFrame = (s.currentFrame);
  numberOfFrames = ( s.numberOfFrames );
  frameInterval = ( s.frameInterval );
  timeSinceLastFrame = ( s.timeSinceLastFrame );
  worldWidth = ( s.worldWidth );
  worldHeight = ( s.worldHeight );
  return *this;
}

void twowaySprite::explode() {
  if(!explosion) {
   Sprite sprite(getName(), getPosition(), getVelocity(), images[currentFrame]);

   explosion = new ExplodingSprite(sprite);
}
}

void twowaySprite::draw() const { 
  if(explosion) explosion->draw(); 
  else images[currentFrame]->draw(getX(), getY(), getScale());
}

void twowaySprite::update(Uint32 ticks) { 
  if ( explosion ) {
    explosion->update(ticks);
    if ( explosion->chunkCount() == 0 ) {
      delete explosion;
      explosion = NULL;
      explosionChecker = true;
    }
    return;
  }

  advanceFrame(ticks);

  Vector2f incr = getVelocity() * static_cast<float>(ticks) * 0.001;
  setPosition(getPosition() + incr);

  if ( getY() < 0) {
      setVelocityY(std::abs(getVelocityY()));
    //setVelocityY( fabs( getVelocityY() ) );
  }
  if ( getY() > worldHeight-getScaledHeight()) {
	setVelocityY( -std::abs(getVelocityY()));
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
