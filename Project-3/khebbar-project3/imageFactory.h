#include <string>
#include <vector>
#include <map>
#include "image.h"
#include "gamedata.h"
#include "spriteSheet.h"

class ImageFactory {
public:

  static ImageFactory& getInstance();
  ~ImageFactory();
   ImageFactory(const ImageFactory&) = delete;
   ImageFactory& operator=(const ImageFactory&) = delete;

   Image* getImage(const std::string&);
   std::vector<Image*> getImages(const std::string&);

private:
  const Gamedata& gdata;

  std::map<std::string, SDL_Surface*> surfaces;
  std::map<std::string, SDL_Texture*> textures;
  std::map<std::string, Image*> images;

  std::map<std::string, std::vector<SDL_Surface*> > multiSurfaces;
  std::map<std::string, std::vector<SDL_Texture*> > multiTextures;
  std::map<std::string, std::vector<Image*> > multiImages;

  ImageFactory() : 
    gdata( Gamedata::getInstance() ), 
    surfaces(),
    textures(),
    images(),
    multiSurfaces(),
    multiTextures(),
    multiImages()
  {}
};
