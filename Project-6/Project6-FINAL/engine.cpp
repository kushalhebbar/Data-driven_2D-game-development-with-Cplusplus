#include <iostream>
#include <algorithm>
#include <sstream>
#include <unistd.h>
#include <string>
#include <random>
#include <iomanip>
#include <vector>
#include "smartSprite.h"
#include "subjectSprite.h"
#include "sprite.h"
#include "multisprite.h"
#include "gamedata.h"
#include "engine.h"
#include "twowaysprite.h"
#include "frameGenerator.h"
#include "player.h"
#include "hud.h"
#include "collisionStrategy.h"
#include "shootingSprite.h"

Engine::~Engine() { 
for(auto sprite : fruits){
	delete sprite;
}
  for(auto sprite : sprites){
	delete sprite;
}
  for(auto sprite : gem){
       delete sprite;
}

delete player;
for( CollisionStrategy* strategy : strategies ) {
	delete strategy;
}
  std::cout << "Terminating program" << std::endl;
}

Engine::Engine() :
  rc( RenderContext::getInstance() ),
  io( IoMod::getInstance() ),
  clock( Clock::getInstance() ),
  renderer( rc->getRenderer() ),
  mountain("mountain", Gamedata::getInstance().getXmlInt("mountain/factor") ),
  lake("lake", Gamedata::getInstance().getXmlInt("lake/factor") ),
  land("land", Gamedata::getInstance().getXmlInt("land/factor") ),
  fruits(),
  gem(),
  sprites(),
  player(new ShootingSprite("dumbo")),
  strategies(),
  currentStrategy(0),
  collision(false),
  viewport( Viewport::getInstance() ),
  lights(),
  currentSprite(0),
  makeVideo( false ),
  showHud(false),
  godmode(false),
  sound()
{
  Vector2f pos = player->getPosition();
  int w = player->getScaledWidth();
  int h = player->getScaledHeight();
  fruits.push_back( new SmartSprite("apple1", pos, w, h) );
  fruits.push_back( new SmartSprite("apple2", pos, w, h) );
  fruits.push_back( new SmartSprite("berry", pos, w, h) );
  fruits.push_back( new SmartSprite("cherry", pos, w, h) );
  fruits.push_back( new SmartSprite("melon", pos, w, h) );
  fruits.push_back( new SmartSprite("pear", pos, w, h) );
  fruits.push_back( new SmartSprite("cherry", pos, w, h) );
  fruits.push_back( new SmartSprite("melon", pos, w, h) );
  fruits.push_back( new SmartSprite("pear", pos, w, h) );

  for(unsigned int i = 0; i<=15;++i){
  gem.push_back( new SmartSprite("gems", pos, w, h) );
  }
  for (unsigned int i = 0; i < gem.size(); ++i) {
    player->attach( gem[i] );
}
  for (unsigned int i = 0; i < fruits.size(); ++i) {
    player->attach( fruits[i] );
}

  sprites.push_back(new twowaySprite("stork"));

  for(unsigned int i=0; i<=7;++i){
  sprites.push_back(new twowaySprite("piranha"));
  }
  sprites.push_back(new twowaySprite("boat"));

  strategies.push_back( new PerPixelCollisionStrategy );
  strategies.push_back( new RectangularCollisionStrategy );
  strategies.push_back( new MidPointCollisionStrategy );

  Viewport::getInstance().setObjectToTrack(player);
  std::cout << "Loading complete" << std::endl;
}

void Engine::draw() const {
  mountain.draw();
  lake.draw();
  land.draw();
  
for(auto sprite : sprites){
	sprite->draw();
}
for(auto sprite : fruits){
  	sprite->draw();
  }

player->draw();

if (fruits.size() > 0){
    std::stringstream strm;
    strm << fruits.size() << " Fruits remaining";
    IoMod::getInstance().writeText(strm.str(), 600, 90);
  }else{  
   usleep(10000);
  
   IoMod::getInstance().writeText("LEVEL 1 DONE!", 550, 110);
   IoMod::getInstance().writeText("GEM RUSH", 550, 130);

  for(auto sprite : gem){
	if(!(sprite->exploded())) 
	sprite->draw();}
	if(gem.size() <= 0){ 
	Hud::getInstance().gamewin(renderer);
	IoMod::getInstance().writeText("    ", 650, 200);
}
}

strategies[currentStrategy]->draw();
  if ( collision ) {
    IoMod::getInstance().writeText("    ", 600, 115);
  }
  drawHud();
  viewport.draw();
  lights.draw();
  
  //Prints name in the bottom left of the screen
  std::stringstream name;
  name <<"Kushal Hebbar" << std::endl;
  io.writeText(name.str(),20,500);

  if(player->exploded()){
  Hud::getInstance().gameover(renderer);
}
  SDL_RenderPresent(renderer);
}

void Engine::checkForCollisions() {
  collision = false;
  for ( const Drawable* d : sprites ) {
    if ( strategies[currentStrategy]->execute(*player, *d) ) {
      collision = true;
    }
  }
  if(!godmode){
  for(unsigned int i=0; i<=7; ++i){
  if(strategies[currentStrategy] -> execute(*sprites[i], *player)) {
    collision = true;
    player -> explode();
  }
}
}
else {
	for(unsigned int i=0; i<=7; ++i){
  	if(strategies[currentStrategy] -> execute(*sprites[i], *player)) {
    	collision = true;
    	sprites[i] -> explode();
  }
}
}
  
  for(const auto d : player->getBullets() ) {
	if(strategies[currentStrategy]->execute(*sprites[0],d)) {
		collision = true;
		sprites[0]->explode();
	}
  }

  auto it = gem.begin();
  while ( it!=gem.end() ) {
   if ( strategies[currentStrategy]->execute(*player, **it) ) {
	SmartSprite* here = *it;
	player->detach(here);
	delete here;
	it = gem.erase(it);
   }
   else ++it;
 }
  
  it = fruits.begin();
  while ( it != fruits.end() ) {
    if ( strategies[currentStrategy]->execute(*player, **it) ) {
      SmartSprite* doa = *it;
      player->detach(doa);
      delete doa;
      it = fruits.erase(it);
    }
    else ++it;
  }

  if ( collision ) {
    player->collided();
  }
  else {
    player->missed();
    collision = false;
  }
}

void Engine::update(Uint32 ticks) {

  checkForCollisions();
  for(auto sprite : fruits){
  	sprite->update(ticks);
  }
  for(auto sprite : sprites){
	sprite -> update(ticks);
}
  for(auto sprite : gem){
	sprite->update(ticks);
}
    
  if(player -> exploded() ){
	clock.pause();
  }

  mountain.update();
  land.update();
  lake.update();
  player->update(ticks);
  lights.update();
  viewport.update(); 
}

void Engine::switchSprite(){
  ++currentSprite;
  currentSprite = currentSprite % sprites.size();
  Viewport::getInstance().setObjectToTrack(sprites.at(currentSprite));
}

void Engine::drawHud() const {
  unsigned int freelistSize = player->getFreeList();
  unsigned int bulletlistSize = player->getBulletList();

  if (showHud || clock.getSeconds() <= 3){
  	Hud::getInstance().draw(renderer);
        Hud::getInstance().drawPool(renderer, bulletlistSize, freelistSize);
  }
 }

bool Engine::play() {
  SDL_Event event;
  const Uint8* keystate;
  bool done = false;
  Uint32 ticks = clock.getElapsedTicks();
  FrameGenerator frameGen;

  while ( !done ) {
    // The next loop polls for events, guarding against key bounce:
    while ( SDL_PollEvent(&event) ) {
      keystate = SDL_GetKeyboardState(NULL);
      if (event.type ==  SDL_QUIT) { done = true; break; }
      if(event.type == SDL_KEYDOWN) {
        if (keystate[SDL_SCANCODE_ESCAPE] || keystate[SDL_SCANCODE_Q]) {
          done = true;
          break;
        }
        if ( keystate[SDL_SCANCODE_P] ) {
          if ( clock.isPaused() ) clock.unpause();
          else clock.pause();
        }
	if ( keystate[SDL_SCANCODE_R] ) {
	    clock.unpause();
	    return true;
	}
        if ( keystate[SDL_SCANCODE_G] ) {
	  godmode = ~godmode;
        }
	if ( keystate[SDL_SCANCODE_SPACE] ) {
		player->shoot();
	}
        if ( keystate[SDL_SCANCODE_T] ) {
          switchSprite();
        }
	if ( keystate[SDL_SCANCODE_M] ) {
          currentStrategy = (1 + currentStrategy) % strategies.size();
        }
        if (keystate[SDL_SCANCODE_F4] && !makeVideo) {
          std::cout << "Initiating frame capture" << std::endl;
          makeVideo = true;
        }
        else if (keystate[SDL_SCANCODE_F4] && makeVideo) {
          std::cout << "Terminating frame capture" << std::endl;
          makeVideo = false;
        }
	if (keystate[SDL_SCANCODE_F1] && !showHud) {
          showHud = true;
        }
        else if (keystate[SDL_SCANCODE_F1] && showHud) {
          showHud = false;
        }
      }
    }

    // In this section of the event loop we allow key bounce:
ticks = clock.getElapsedTicks();
    if ( ticks > 0 ) {
      clock.incrFrame();
      if (keystate[SDL_SCANCODE_A]) {
        player->left();
      }
      if (keystate[SDL_SCANCODE_D]) {
        player->right();
      }
      if (keystate[SDL_SCANCODE_W]) {
        player->up();
      }
      if (keystate[SDL_SCANCODE_S]) {
        player->down();
      }
      draw();
      update(ticks);
      if ( makeVideo ) {
        frameGen.makeFrame();
      }
    }
  }
return false;
}
