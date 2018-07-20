#include <iostream>
#include <algorithm>
#include <sstream>
#include <string>
#include <random>
#include <iomanip>
#include "sprite.h"
#include "multisprite.h"
#include "gamedata.h"
#include "engine.h"
#include "twowaysprite.h"
#include "frameGenerator.h"

Engine::~Engine() { 
  for(auto sprite : sprites){
	delete sprite;
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
  viewport( Viewport::getInstance() ),
  currentSprite(0),
  makeVideo( false )
{
  
  for(unsigned int i=0;i<=7;++i){
  sprites.push_back(new twowaySprite("bird"));
}
  sprites.push_back(new twowaySprite("boat")),
  sprites.push_back(new twowaySprite("dora")),
  sprites.push_back(new Sprite("pokeball")),
  Viewport::getInstance().setObjectToTrack(sprites.at(currentSprite));
  std::cout << "Loading complete" << std::endl;
}

void Engine::draw() const {
  mountain.draw();
  lake.draw();
  land.draw();
  
for(auto sprite : sprites){
	sprite->draw();
}
  viewport.draw();
  SDL_Color textcolor = {255,255,255,0};
//Calculate the Frames Per Second
  std::stringstream fps;
  fps << "FPS:" << clock.getFps();
  io.writeText(fps.str(),20,70, textcolor);
  
  //Prints name in the bottom left of the screen
  std::stringstream name;
  name <<"Kushal Hebbar" << std::endl;
  io.writeText(name.str(),20,500);

  SDL_RenderPresent(renderer);
}

void Engine::update(Uint32 ticks) {
  for(auto sprite : sprites){
	sprite -> update(ticks);
}
  mountain.update();
  land.update();
  lake.update();
  viewport.update(); // always update viewport last
}

void Engine::switchSprite(){
  ++currentSprite;
  currentSprite = currentSprite % sprites.size();
  Viewport::getInstance().setObjectToTrack(sprites.at(currentSprite));
}

void Engine::play() {
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
        if ( keystate[SDL_SCANCODE_T] ) {
          switchSprite();
        }
        if (keystate[SDL_SCANCODE_F4] && !makeVideo) {
          std::cout << "Initiating frame capture" << std::endl;
          makeVideo = true;
        }
        else if (keystate[SDL_SCANCODE_F4] && makeVideo) {
          std::cout << "Terminating frame capture" << std::endl;
          makeVideo = false;
        }
      }
    }

    // In this section of the event loop we allow key bounce:

    ticks = clock.getElapsedTicks();
    if ( ticks > 0 ) {
      clock.incrFrame();
      draw();
      update(ticks);
      if ( makeVideo ) {
        frameGen.makeFrame();
      }
    }
  }
}
