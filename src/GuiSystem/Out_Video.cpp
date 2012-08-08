#include <XGraph/GuiSystem/OutVideo.h>
#include <XGraph/GuiSystem/XG_Screen.h>

const Uint32 OutVideo::sdl_flag_need=SDL_INIT_TIMER| SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_EVENTTHREAD;


OutVideo* OutVideo::m_pInstance=NULL;
OutVideo::OutVideo(void):w_screen(0),h_screen(0),_fps_last_call(0),fps_current(0){

}
OutVideo::OutVideo(const OutVideo& oth){

}
OutVideo& OutVideo::operator=(const OutVideo& oth){
	return *this;
}





const bool OutVideo::Check_SDLINIT(void){
	Uint32 resp=SDL_WasInit(OutVideo::sdl_flag_need);
	if(resp&OutVideo::sdl_flag_need){
		return true;
	}
	return false;
}
void OutVideo::OpenSDL_FORCE(void){
	if(OutVideo::Check_SDLINIT()==false){
		SDL_Init(OutVideo::sdl_flag_need);
	}
}
void OutVideo::CloseSDL_FORCE(void){
	if(OutVideo::Check_SDLINIT()==true){
		SDL_Quit();
	}
}



bool OutVideo::Create_Window(const Setting_Window& set){
	OutVideo::OpenSDL_FORCE();
	Uint32 flag=SDL_HWSURFACE | SDL_ANYFORMAT | SDL_DOUBLEBUF;
	if(set.fullscreen){
		flag=flag | SDL_FULLSCREEN;
	}
	this->_screen=SDL_SetVideoMode(set.width,set.height,set.bpp,flag);
	if(this->_screen.Is_Load()==false){
		this->last_error="Impossibile inizializzare la finestra grafica!\n";
		this->last_error+=SDL_GetError();
		return false;
	}
	this->w_screen=(Sint16)(set.width);
	this->h_screen=(Sint16)(set.height);
	XG_Screen::Get_Instance().Load(NULL);
	return true;
}
void OutVideo::Destroy_Window(void){
	XG_Screen::Get_Instance().UnLoad();
	this->_screen.Delete();
	this->w_screen=0;
	this->h_screen=0;
}