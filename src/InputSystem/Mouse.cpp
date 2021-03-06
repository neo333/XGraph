#include <XGraph/InputSystem/Mouse.h>

Mouse::Mouse(void):_bleft(false),_bright(false),_bmiddle(false),skin_normal_loaded(false),skin_load_loaded(false),mode_load(false){

}
Mouse::Mouse(const Mouse& oth){

}
Mouse& Mouse::operator=(const Mouse& oth){
	return *this;
}
Mouse* Mouse::m_pInstance=NULL;



void Mouse::SetNormalSkin(const Texture& text){
	if(text.Is_Load()==true){
		this->skin_normal = text;
		this->skin_normal_loaded=true;
		SDL_ShowCursor(SDL_DISABLE);
	}else{
		this->skin_normal_loaded=false;
		SDL_ShowCursor(SDL_ENABLE);
	}
}

void Mouse::SetLoadSkin(const Texture& text){
	if(text.Is_Load()==true){
		this->skin_load = text;
		this->skin_load_loaded=true;
	}else{
		this->skin_load_loaded=false;
	}
}