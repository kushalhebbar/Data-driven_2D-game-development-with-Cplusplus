#include <vector>
#include <SDL.h>
#include "ioMod.h"
#include "renderContext.h"
#include "clock.h"
#include "world.h"
#include "lights.h"
#include "viewport.h"
#include "sound.h"
#include "smartSprite.h"

class ShootingSprite;
class CollisionStrategy;

class Engine {
public:
  Engine ();
  ~Engine ();
  Engine(const Engine&) = delete;
  Engine& operator=(const Engine&) = delete;
  bool play();
  void switchSprite();

private:
  const RenderContext* rc;
  const IoMod& io;
  Clock& clock;

  SDL_Renderer * const renderer;

  World mountain;
  World lake;
  World land;

  std::vector <SmartSprite*> fruits;
  std::vector <SmartSprite*> gem;
  std::vector<Drawable*> sprites;
  ShootingSprite* player;
  std::vector<CollisionStrategy*> strategies;
  int currentStrategy;
  bool collision;

  Viewport& viewport;
  Lights lights;
  int currentSprite;
  
  bool makeVideo;
  bool showHud;
  bool godmode;
  SDLSound sound;

  void draw() const;
  void drawHud() const;
  void update(Uint32);

  void printScales() const;
  void checkForCollisions();
};
