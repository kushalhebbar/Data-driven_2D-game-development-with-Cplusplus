#ifndef HUD_H_
#define HUD_H_

#include <string>
#include "ioMod.h"
#include "gamedata.h"
#include <SDL.h>

class Hud{
public:
  static Hud& getInstance();
  void gameover(SDL_Renderer * const);
  void gamewin(SDL_Renderer * const);
  void draw(SDL_Renderer * const);
  void drawPool(SDL_Renderer * const, unsigned int, unsigned int);
  ~Hud();
private:
  const IoMod& io;
  const Gamedata& gdata;
  Hud();
  Hud(const Hud&);
  Hud& operator=(const Hud&);
};

#endif
