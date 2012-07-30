#ifndef __OUTVIDEO__GUI
#define __OUTVIDEO__GUI

#include <XGraph/GuiSystem/Texture.h>
#include <cassert>

struct Setting_Window{
	int width;
	int height;
	int bpp;
	bool fullscreen;

	Setting_Window(const int& w_loc, const int& h_loc, const int& bpp_loc, const bool& f_loc):width(w_loc),
		height(h_loc),bpp(bpp_loc),fullscreen(f_loc){

	}
};

class Image;

class OutVideo{

public:		//INTERFACCIA
	/*Ritorna il singleton della classe.
	In alternativa è possibile utilizzare la macro 'Screen' e manipolare 'Screen' come se fosse l'oggetto video*/
	static OutVideo& Get_Instance(void){
		if(OutVideo::m_pInstance==NULL){
			OutVideo::m_pInstance=new OutVideo();
			assert(OutVideo::m_pInstance);
		}
		return *OutVideo::m_pInstance;
	}
	~OutVideo(void){
		OutVideo::Check_SDLINIT();
	}
	
public:		//INIZIALIZZATORI
	/*Crea la finestra grafica dell'applicazione.
	Questa funzione deve essere chiamata appena dopo aver inizializzato la libreria SDL.
	
	NOTA:
		Questa funzione controlla se la libreria SDL è stata inizializzata, in caso negativo
		proverà una forzatura nell'inizializzazione della stessa*/
	bool Create_Window(const Setting_Window& set){
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
		return true;
	}
	void Destroy_Window(void){
		this->_screen.Delete();
		this->w_screen=0;
		this->h_screen=0;
	}
	void Set_TitleWindow(const std::string& setter){
		SDL_WM_SetCaption(setter.c_str(), NULL);
	}



public:		//METODI GET&SET
	const std::string& Get_LastError(void) const{
		return this->last_error;
	}
	const Sint16& Get_W_Screen(void) const{
		return this->w_screen;
	}
	const Sint16& Get_H_Screen(void) const{
		return this->h_screen;
	}
	SDL_Surface* Get_Surface(void){
		return (SDL_Surface*)(this->_screen);
	}
	const Uint8 Get_BitPerPixel_Depth(void) const{
		const SDL_Surface* _p=this->_screen;
		return _p->format->BitsPerPixel;
	}


public:		//REFRESH SCHERMO
	const bool UpDateScreen(void){
		static unsigned int _fps_var=0;
		static Uint32 time_curr=0;

		time_curr=SDL_GetTicks();
		if(time_curr-this->_fps_last_call >= 1000){
			this->_fps_last_call=time_curr;
			this->fps_current=_fps_var;
			_fps_var=0;
		}

		if(SDL_Flip(this->_screen.Get_Surface())!=0){
			this->last_error="Impossibile eseguire il flip dello schermo!\n";
			this->last_error+=SDL_GetError();
			return false;
		}else{
			_fps_var++;
		}
		return true;
	}
	const unsigned int& Get_Current_FPS(void) const{
		return this->fps_current;
	}











private:		//FUNZIONI MEMBRO PRIVATE E DATA
	friend class Image;

	OutVideo(void);
	OutVideo(const OutVideo&);
	OutVideo& operator=(const OutVideo&);
	static OutVideo* m_pInstance;

	std::string last_error;

	Texture _screen;
	Sint16 w_screen;
	Sint16 h_screen;

	Uint32 _fps_last_call;
	unsigned int fps_current;

private:		//FUNZIONI DI SUPPORTO PRIVATE
	static const bool Check_SDLINIT(void);
	static void OpenSDL_FORCE(void);
	static void CloseSDL_FORCE(void);
	static const Uint32 sdl_flag_need;
};

#define Screen OutVideo::Get_Instance()

#endif