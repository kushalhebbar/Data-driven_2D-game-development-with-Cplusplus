#include <vector>
#include <SDL.h>
#include "ioMod.h"
#include "renderContext.h"
#include "clock.h"
#include "world.h"
#include "viewport.h"
#include "smartSprite.h"

class SubjectSprite;
class CollisionStrategy;

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

  std::vector <SmartSprite*> fruits;
  std::vector<Drawable*> sprites;
  SubjectSprite* player;
  std::vector<CollisionStrategy*> strategies;
  int currentStrategy;
  bool collision;

  Viewport& viewport;
  int currentSprite;

  bool makeVideo;
  bool showHud;

  void draw() const;
  void drawHud() const;
  void update(Uint32);

  void printScales() const;
  void checkForCollisions();
};
