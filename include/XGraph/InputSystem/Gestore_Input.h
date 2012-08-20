#ifndef __GESTORE_INPUT__IS
#define __GESTORE_INPUT__IS

#include <SDL/SDL.h>
#include <cassert>
#include <XGraph/InputSystem/Mouse.h>
#include <XGraph/InputSystem/Tastiera.h>

class Gestore_Input{
public:
	static Gestore_Input& Get_Instance(void){
		if(Gestore_Input::m_pInstance==NULL){
			Gestore_Input::m_pInstance=new Gestore_Input();
			SDL_EnableKeyRepeat(SDL_DEFAULT_REPEAT_DELAY, SDL_DEFAULT_REPEAT_INTERVAL);
			SDL_EnableUNICODE(1);
			assert(Gestore_Input::m_pInstance);
		}
		return *Gestore_Input::m_pInstance;
	}

	/*Aggiorna tutti gli stati input del sistema*/
	void UpDateAll(void){
		if(SDL_PollEvent(&this->_int_events)){
			switch(this->_int_events.type){
			case SDL_QUIT:
				this->force_quit_app=true;
				break;
			case SDL_MOUSEMOTION:
				this->UpDateMousePosition();
				break;
			case SDL_MOUSEBUTTONDOWN:
				this->UpDateMouseDownButt();
				break;
			case SDL_MOUSEBUTTONUP:
				this->UpDateMouseUpButt();
				break;
			case SDL_KEYDOWN:
				this->UpDateKeyDown();
				break;
			case SDL_KEYUP:
				this->UpDateKeyUp();
				break;
			}
		}
	}

	/*Ritorna true se un evento ha richiesto la chiusura forzata dell'applicazione*/
	const bool& Check_ExitApp(void) const{
		return this->force_quit_app;
	}

	/*Forza la chiusura dell'applicazione, eventualmente mandando un messaggio*/
	void Set_ForceCloseApp(const std::string& mess){
		this->mess_force_close=mess;
		this->force_quit_app=true;
	}


















private:		//INTERNAL DATA
	SDL_Event _int_events;	//lista di eventi
	bool force_quit_app;
	std::string mess_force_close;





private:		//INTERNAL FUNCTIONS

	inline void UpDateMousePosition(void){
		Mouse::Get_Instance().x=this->_int_events.motion.x;
		Mouse::Get_Instance().y=this->_int_events.motion.y;
		if(Mouse::Get_Instance().skin_normal_loaded==true){
			Mouse::Get_Instance().skin_normal.Set_Position(Point(this->_int_events.motion.x,this->_int_events.motion.y));
		}
		if(Mouse::Get_Instance().skin_load_loaded==true){
			Mouse::Get_Instance().skin_load.Set_Position(Point(this->_int_events.motion.x,this->_int_events.motion.y));
		}
	}
	void UpDateMouseDownButt(void){
		switch(this->_int_events.button.button){
		case SDL_BUTTON_LEFT:
			Mouse::Get_Instance()._bleft=true;
			Mouse::Get_Instance().last_clic.button_type_clic=TMB_LEFT;
			break;
		case SDL_BUTTON_MIDDLE:
			Mouse::Get_Instance()._bmiddle=true;
			Mouse::Get_Instance().last_clic.button_type_clic=TMB_MIDDLE;
			break;
		case SDL_BUTTON_RIGHT:
			Mouse::Get_Instance().last_clic.button_type_clic=TMB_RIGHT;
			Mouse::Get_Instance()._bright=true;
			break;
		}
		Mouse::Get_Instance().last_clic.x_clic=this->_int_events.button.x;
		Mouse::Get_Instance().last_clic.y_clic=this->_int_events.button.y;

	}
	void UpDateMouseUpButt(void){
		switch(this->_int_events.button.button){
		case SDL_BUTTON_LEFT:
			Mouse::Get_Instance()._bleft=false;
			Mouse::Get_Instance().last_release.button_type_clic=TMB_LEFT;
			break;
		case SDL_BUTTON_MIDDLE:
			Mouse::Get_Instance()._bmiddle=false;
			Mouse::Get_Instance().last_release.button_type_clic=TMB_LEFT;
			break;
		case SDL_BUTTON_RIGHT:
			Mouse::Get_Instance()._bright=false;
			Mouse::Get_Instance().last_release.button_type_clic=TMB_LEFT;
			break;
		}
		Mouse::Get_Instance().last_release.x_clic=this->_int_events.button.x;
		Mouse::Get_Instance().last_release.y_clic=this->_int_events.button.y;
	}

	void UpDateKeyDown(void){
		ctrl_Tastiera.Put_into_Buffer(this->_int_events.key.keysym.unicode);
		ctrl_Tastiera.UpDate_Array_Key();
	}
	void UpDateKeyUp(void){
		ctrl_Tastiera.UpDate_Array_Key();
	}

	






private:	//SINGLETON REALIZATION
	Gestore_Input(void);
	Gestore_Input(const Gestore_Input&);
	Gestore_Input& operator=(const Gestore_Input&);
	static Gestore_Input* m_pInstance;
};

#define SysInput Gestore_Input::Get_Instance()

#endif