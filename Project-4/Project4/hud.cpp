#include <iostream>
#include <string>
#include <sstream>
#include <SDL.h>
#include "hud.h"

Hud& Hud::getInstance() {
  static Hud instance;
  return instance;
}
Hud::Hud() :
  io( IoMod::getInstance() ),
  gdata( Gamedata::getInstance() ) {
}

Hud::~Hud(){}

void Hud::draw(SDL_Renderer * const renderer){
  SDL_Rect box;
  box.x = gdata.getXmlInt("hud/posX");
  box.y = gdata.getXmlInt("hud/posY");
  box.w = gdata.getXmlInt("hud/width");
  box.h = gdata.getXmlInt("hud/height");
  int borderThickness = gdata.getXmlInt("hud/border/thickness");
  SDL_Color borderColor;
  borderColor.r = gdata.getXmlInt("hud/border/Color/red");
  borderColor.g = gdata.getXmlInt("hud/border/Color/green");
  borderColor.b = gdata.getXmlInt("hud/border/Color/blue");
  borderColor.a = gdata.getXmlInt("hud/border/Color/alpha");
  SDL_SetRenderDrawColor(renderer, borderColor.r, borderColor.g, borderColor.b, borderColor.a);
  for(int i =1; i<=borderThickness; i++){
    SDL_RenderDrawRect(renderer, &box);
    box.x += 1;
    box.y += 1;
    box.w -= 2;
    box.h -= 2;
  }
  SDL_Color background;
  background.r = gdata.getXmlInt("hud/hudColor/red");
  background.g = gdata.getXmlInt("hud/hudColor/green");
  background.b = gdata.getXmlInt("hud/hudColor/blue");
  background.a = gdata.getXmlInt("hud/hudColor/alpha");
  SDL_SetRenderDrawColor(renderer, background.r, background.g, background.b, background.a);
  SDL_RenderFillRect(renderer, &box);
  SDL_Color textColor;
  textColor.r = gdata.getXmlInt("hud/textColor/red");
  textColor.g = gdata.getXmlInt("hud/textColor/green");
  textColor.b = gdata.getXmlInt("hud/textColor/blue");
  textColor.a = gdata.getXmlInt("hud/textColor/alpha");
  io.writeText(gdata.getXmlStr("hud/text").c_str(), box.x+=15, box.y+=15, textColor);
  io.writeText(gdata.getXmlStr("hud/up").c_str(), box.x, box.y+=30, textColor);
  io.writeText(gdata.getXmlStr("hud/left").c_str(), box.x, box.y+=30, textColor);
  io.writeText(gdata.getXmlStr("hud/down").c_str(), box.x, box.y+=30, textColor);
 io.writeText(gdata.getXmlStr("hud/right").c_str(), box.x, box.y+=30, textColor);
 io.writeText(gdata.getXmlStr("hud/pause").c_str(), box.x, box.y+=30, textColor);
  io.writeText(gdata.getXmlStr("hud/collision").c_str(), box.x, box.y+=30, textColor);
  io.writeText(gdata.getXmlStr("hud/hudshow").c_str(), box.x, box.y+=30, textColor);
}

