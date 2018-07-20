#include <iostream>
#include <SDL2/SDL.h>
#include "frameGenerator.h"
#include "draw.h"

const int WINDOW_WIDTH = 900;
const int WINDOW_HEIGHT = 600;
const std::string NAME = "khebbar";
const std::string TITLE = "A day on the lake";

int main(void) {
  SDL_Renderer *renderer=nullptr;
  SDL_Window *window=nullptr;

  Draw boat(renderer, window, WINDOW_WIDTH, WINDOW_HEIGHT, TITLE);
  std::cout << boat << "\n";
  boat.drawBoat();
  boat.genFrame();

  SDL_Event event;
  const Uint8* keystate;
  while ( true ) {
    keystate = SDL_GetKeyboardState(0);
    if (keystate[SDL_SCANCODE_ESCAPE]) { break; }
    if (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        break;
      }
    }
  }
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
  return EXIT_SUCCESS;
}
