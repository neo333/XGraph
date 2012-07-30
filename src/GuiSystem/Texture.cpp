#include <XGraph/GuiSystem/Texture.h>
#include <XGraph/GuiSystem/OutVideo.h>

Texture::Texture(const int n_width, const int n_height){
	this->mp_surface=SDL_CreateRGBSurface(SDL_HWSURFACE | SDL_SRCCOLORKEY | SDL_SRCALPHA, n_width, n_height, Screen.Get_BitPerPixel_Depth() , 0x00ff0000, 0x0000ff00, 0x000000ff, 0x00000000);
}