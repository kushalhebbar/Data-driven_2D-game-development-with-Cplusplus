#include <string>
#include <SDL2/SDL.h>

const double PI = 3.1415926535897;
const double D2R = PI/180;

class Draw{
public:
  Draw(SDL_Renderer*, SDL_Window*, int, int, std::string);
  double d2r(double x);
  void drawRect(SDL_Renderer*);
  void drawTriangle(SDL_Renderer*);
  void drawCircle(SDL_Renderer* renderer, SDL_Point center, int radius, SDL_Color color);
  void drawBoat();
  void genFrame();
  void drawPaddle(SDL_Renderer*);
  void drawMan(SDL_Renderer*);
  void drawWater(SDL_Renderer*);
  const std::string getTitle() const;
  int getWidth() const;
  int getHeight() const;

private:
  SDL_Renderer* renderer;
  SDL_Window*  window;
  const int WIDTH;
  const int HEIGHT;
  const std::string TITLE;
};

std::ostream& operator <<(std::ostream& out, const Draw& d); 
