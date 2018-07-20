#include <vector>
#include <SDL.h>
#include "ioMod.h"
#include "renderContext.h"
#include "clock.h"
#include "world.h"
#include "viewport.h"

class Engine {
public:
  Engine ();
  ~Engine ();
  Engine(const Engine&) = delete;
  Engine& operator=(const Engine&) = delete;
  void play();
  void switchSprite();

private:
  const RenderContext* rc;
  const IoMod& io;
  Clock& clock;

  SDL_Renderer * const renderer;

  World mountain;
  World lake;
  World land;

  Viewport& viewport;

  std::vector<Drawable*> sprites;

  int currentSprite;

  bool makeVideo;

  void draw() const;
  void update(Uint32);

  void printScales() const;
  void checkForCollisions();
};
