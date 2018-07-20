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

void Hud::drawPool(SDL_Renderer * const renderer, unsigned int bulletlistSize, unsigned int freelistSize){
  SDL_Rect rect;
  rect.x = gdata.getXmlInt("hud/Pool/posX");
  rect.y = gdata.getXmlInt("hud/Pool/posY");
  rect.w = gdata.getXmlInt("hud/Pool/width");
  rect.h = gdata.getXmlInt("hud/Pool/height");
  int borderThickness = gdata.getXmlInt("hud/border/thickness");
  SDL_Color borderColor;
  borderColor.r = gdata.getXmlInt("hud/border/Color/red");
  borderColor.g = gdata.getXmlInt("hud/border/Color/green");
  borderColor.b = gdata.getXmlInt("hud/border/Color/blue");
  borderColor.a = gdata.getXmlInt("hud/border/Color/alpha");
  SDL_SetRenderDrawColor(renderer, borderColor.r, borderColor.g, borderColor.b, borderColor.a);
  for(int i =1; i<=borderThickness; i++){
    SDL_RenderDrawRect(renderer, &rect);
    rect.x += 1;
    rect.y += 1;
    rect.w -= 2;
    rect.h -= 2;
  }
  SDL_Color background;
  background.r = gdata.getXmlInt("hud/hudColor/red");
  background.g = gdata.getXmlInt("hud/hudColor/green");
  background.b = gdata.getXmlInt("hud/hudColor/blue");
  background.a = gdata.getXmlInt("hud/hudColor/alpha");
  SDL_SetRenderDrawColor(renderer, background.r, background.g, background.b, background.a);
  SDL_RenderFillRect(renderer, &rect);
  
  SDL_Color textColor;
  textColor.r = gdata.getXmlInt("hud/textColor/red");
  textColor.g = gdata.getXmlInt("hud/textColor/green");
  textColor.b = gdata.getXmlInt("hud/textColor/blue");
  textColor.a = gdata.getXmlInt("hud/textColor/alpha");
  std::stringstream freelist;
  freelist << "FreeList:\t  " << freelistSize;
  io.writeText(freelist.str(), rect.x+=5, rect.y+=5, textColor);
  std::stringstream bulletlist;
  bulletlist << "BulletList:\t" << bulletlistSize;
  io.writeText(bulletlist.str(), rect.x, rect.y+=30, textColor);
  
}

void Hud::draw(SDL_Renderer * const renderer){
  SDL_Rect rect;
  rect.x = gdata.getXmlInt("hud/posX");
  rect.y = gdata.getXmlInt("hud/posY");
  rect.w = gdata.getXmlInt("hud/width");
  rect.h = gdata.getXmlInt("hud/height");
  int borderThickness = gdata.getXmlInt("hud/border/thickness");
  SDL_Color borderColor;
  borderColor.r = gdata.getXmlInt("hud/border/Color/red");
  borderColor.g = gdata.getXmlInt("hud/border/Color/green");
  borderColor.b = gdata.getXmlInt("hud/border/Color/blue");
  borderColor.a = gdata.getXmlInt("hud/border/Color/alpha");
  SDL_SetRenderDrawColor(renderer, borderColor.r, borderColor.g, borderColor.b, borderColor.a);
  for(int i =1; i<=borderThickness; i++){
    SDL_RenderDrawRect(renderer, &rect);
    rect.x += 1;
    rect.y += 1;
    rect.w -= 2;
    rect.h -= 2;
  }
  SDL_Color background;
  background.r = gdata.getXmlInt("hud/hudColor/red");
  background.g = gdata.getXmlInt("hud/hudColor/green");
  background.b = gdata.getXmlInt("hud/hudColor/blue");
  background.a = gdata.getXmlInt("hud/hudColor/alpha");
  SDL_SetRenderDrawColor(renderer, background.r, background.g, background.b, background.a);
  SDL_RenderFillRect(renderer, &rect);
  SDL_Color textColor;
  textColor.r = gdata.getXmlInt("hud/textColor/red");
  textColor.g = gdata.getXmlInt("hud/textColor/green");
  textColor.b = gdata.getXmlInt("hud/textColor/blue");
  textColor.a = gdata.getXmlInt("hud/textColor/alpha");
  io.writeText(gdata.getXmlStr("hud/text").c_str(), rect.x+=15, rect.y+=15, textColor);
  io.writeText(gdata.getXmlStr("hud/up").c_str(), rect.x, rect.y+=30, textColor);
  io.writeText(gdata.getXmlStr("hud/left").c_str(), rect.x, rect.y+=30, textColor);
  io.writeText(gdata.getXmlStr("hud/down").c_str(), rect.x, rect.y+=30, textColor);
 io.writeText(gdata.getXmlStr("hud/right").c_str(), rect.x, rect.y+=30, textColor);
 io.writeText(gdata.getXmlStr("hud/pause").c_str(), rect.x, rect.y+=30, textColor);
io.writeText(gdata.getXmlStr("hud/space").c_str(), rect.x, rect.y+=30, textColor);
  io.writeText(gdata.getXmlStr("hud/collision").c_str(), rect.x, rect.y+=30, textColor);
  io.writeText(gdata.getXmlStr("hud/hudshow").c_str(), rect.x, rect.y+=30, textColor);
}

