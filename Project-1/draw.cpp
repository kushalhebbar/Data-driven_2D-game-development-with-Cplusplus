#include <iostream>
#include <string>
#include "draw.h"
#include "frameGenerator.h"

Draw::Draw(SDL_Renderer* rend, SDL_Window*  win, int w, int h, std::string t) : renderer(rend), window(win), WIDTH(w),HEIGHT(h),TITLE (t){
  SDL_CreateWindowAndRenderer(WIDTH, HEIGHT, 0, &window, &renderer);
  SDL_SetWindowTitle(window, TITLE.c_str());
  SDL_SetRenderDrawColor( renderer, 255, 255, 255, 255 );
  SDL_RenderClear(renderer);
}

double Draw::d2r(double x){
  return x *D2R;
}

//The two sides of the boat attached to the Center rectangle
void Draw::drawTriangle(SDL_Renderer* renderer){

  SDL_SetRenderDrawColor( renderer, 139, 69, 19, 255 );//Brown

  SDL_RenderDrawLine(renderer, 250, 380, 140, 380);
  SDL_RenderDrawLine(renderer, 140, 380, 250, 500);

  SDL_RenderDrawLine(renderer, 600, 380, 710, 380);
  SDL_RenderDrawLine(renderer, 710, 380, 600, 500);
  
  //Used the for loop to fill the color within the two triangles by continously drawing adjacent lines
  for(int i=380;i<=500;i++){
    SDL_RenderDrawLine(renderer, 250, i, 140, 380);
  }

  for(int i=380;i<=500;i++){
    SDL_RenderDrawLine(renderer, 600, i, 710, 380);
  }
}

//Function to generate all the circles in the drawing
void Draw::drawCircle(SDL_Renderer* renderer,SDL_Point center, int radius, SDL_Color color) {
  SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
  for (int w = 0; w < radius * 2; w++) {
    for (int h = 0; h < radius * 2; h++) {
      int dx = radius - w;
      int dy = radius - h; 
      if ((dx*dx + dy*dy) <= (radius * radius)) {
        SDL_RenderDrawPoint(renderer, center.x + dx, center.y + dy);
	}
    }
  }
}

//Function to generate the center rectangle for the boat
void Draw::drawRect(SDL_Renderer* renderer){

   SDL_Rect r;
  r.x = 250;
  r.y = 380;
  r.w = 350;
  r.h = 120;

  SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
  SDL_SetRenderDrawColor( renderer, 139, 69, 19, 255 ); //Brown
  int SDL_RenderFillRect(SDL_Renderer*   renderer,
                       const SDL_Rect* rect);

  SDL_RenderFillRect( renderer, &r );
}

//Function to draw the paddle
void Draw::drawPaddle(SDL_Renderer* renderer){

  SDL_SetRenderDrawColor( renderer, 0,0,0, 255 ); //Black
  SDL_Rect r;
  r.x = 250;
  r.y = 480;
  r.w = 80;
  r.h = 30;

  SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
  int SDL_RenderFillRect(SDL_Renderer*   renderer,
                       const SDL_Rect* rect);

  SDL_RenderFillRect( renderer, &r );
  
  for(int i=0;i<=22;i++){
    SDL_RenderDrawLine(renderer, 240-i, 340, 350-i, 600);  
  }
}
     
//Function to draw the man in the boat
void Draw::drawMan(SDL_Renderer* renderer){

  SDL_SetRenderDrawColor(renderer, 234,192,134, 255 ); //Skin
  for(int i=0;i<=20;i++){
    SDL_RenderDrawLine(renderer, 330, i+280, 250, i+360);
  }

  SDL_Rect r;
  r.x = 312;
  r.y = 270;
  r.w = 110;
  r.h = 110;

  SDL_SetRenderDrawColor(renderer, 94,116,97,255 ); //Military green
  int SDL_RenderFillRect(SDL_Renderer*   renderer,
                       const SDL_Rect* rect);

  SDL_RenderFillRect( renderer, &r );
  
  SDL_SetRenderDrawColor(renderer, 94,116,97,255); //Military green
  for(int i=0;i<=25;i++){
    SDL_RenderDrawLine(renderer, 312, i+290, 280, i+330);
  }

  SDL_SetRenderDrawColor(renderer, 94,116,97,255); //Military green

  for(int i=0;i<=20;i++){
	SDL_RenderDrawLine(renderer,400,i+288,490,i+288);
  }
  SDL_SetRenderDrawColor(renderer, 234,192,134,255); 

  for(int i=0;i<=20;i++){
	SDL_RenderDrawLine(renderer,490,i+288,530,i+288);
  }
}

//Function to draw water
void Draw::drawWater(SDL_Renderer* renderer){
   
  SDL_Rect r;
  r.x = 0;
  r.y = 500;
  r.w = 900;
  r.h = 200;

  SDL_SetRenderDrawColor( renderer, 135,206,250, 255 ); //Light blue
  int SDL_RenderFillRect(SDL_Renderer*   renderer,
                       const SDL_Rect* rect);

  SDL_RenderFillRect( renderer, &r );

  SDL_SetRenderDrawColor( renderer, 135,206,250, 255 ); //Light blue
  SDL_RenderDrawRect( renderer, &r );
}

//Function that calls all other functions in the program
void Draw::drawBoat() {
  //Center points for all circles
  SDL_Point centerSun = {780, 80};
  SDL_Point center1 = {70, 90};
  SDL_Point center2 = {170, 90};
  SDL_Point center3 = {135,60};
  SDL_Point center4 = {90,43};
  SDL_Point centerButton1 = {367,300};
  SDL_Point centerButton2 = {367,330};
  SDL_Point centerButton3 = {367,360};			 
  SDL_Point centerMouth = {370,252};
  SDL_Point centerEye1 = {352,230};
  SDL_Point centerEye2 = {388,230};
  SDL_Point centerHead = {370,240};

  //Radius for all circles
  int radius = 45;
  int radius2 = 40;
  int radius3 = 20;
  int radiusEye = 5;
  int radiusMouth = 10;  
  int radiusButton = 5;

  //Colors for all circles
  SDL_Color skin = {234,192,134,255};
  SDL_Color orange = {255,108,0,255};
  SDL_Color grey = {169,169,169,255};
  SDL_Color white = {255,255,255,255};
  SDL_Color black = {0,0,0,255};
 
  //Calling functions defined in the program
  drawRect(renderer);
  drawTriangle(renderer);
  drawMan(renderer);
  drawPaddle(renderer);
  drawWater(renderer);
  
  //Calling drawCircle function with different parameters
  drawCircle(renderer,centerHead,radius2,skin);
  drawCircle(renderer,centerSun,radius,orange);
  drawCircle(renderer,center1,radius,grey);
  drawCircle(renderer,center2,radius,grey);
  drawCircle(renderer,center3,radius,grey);
  drawCircle(renderer,center4,radius3,grey);
  drawCircle(renderer,centerEye1,radiusEye,white);
  drawCircle(renderer,centerEye2,radiusEye,white);
  drawCircle(renderer,centerMouth,radiusMouth,white);
  drawCircle(renderer,centerButton1,radiusButton,black);
  drawCircle(renderer,centerButton2,radiusButton,black);
  drawCircle(renderer,centerButton3,radiusButton,black);
  
  //Rectangle for bottom half of the cloud
  SDL_SetRenderDrawColor( renderer, 255, 255, 255, 255 ); //White color
  SDL_Rect r;
  r.x = 10;
  r.y = 90;
  r.w = 250;
  r.h = 200;
  SDL_RenderFillRect( renderer, &r );

  //Rectangle for mouth
  SDL_SetRenderDrawColor( renderer, 234,192,134, 255 ); //Skin color
  
  r.x = 360;
  r.y = 240;
  r.w = 24;
  r.h = 14;
  SDL_RenderFillRect( renderer, &r );

  SDL_RenderPresent(renderer);
  genFrame();
}

void Draw::genFrame(){
  FrameGenerator frameGen(renderer, window, WIDTH, HEIGHT, "khebbar");
  frameGen.makeFrame();
}

const std::string Draw::getTitle() const {return TITLE;}

int Draw::getWidth() const {return WIDTH;}

int Draw::getHeight() const {return HEIGHT;}

//Prints string onto console
std::ostream& operator<<(std::ostream& out, const Draw& d){
  return out <<"Rendering " << d.getTitle()<< "\nBAZINGA!\n";
} 

