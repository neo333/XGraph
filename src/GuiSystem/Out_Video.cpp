#include <XGraph/GuiSystem/OutVideo.h>

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