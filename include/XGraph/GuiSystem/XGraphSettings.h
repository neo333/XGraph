#ifndef __XGRAPH_SETTINGS__GUI
#define __XGRAPH_SETTINGS__GUI

#include <SDL/SDL.h>
#include <cassert>

class XGraphSettings{
public:		//INTERFACCIA UTENTE
	void DefaultSetting(void);

	void Set_AlphaLibrary(const Uint8 setter){
		/*Setta il canale globale di trasparenza della libreria.
		Questo canale viene utilizzato da alcune 'classi' per la propria costruzione.
		Ad esempio la creazione di un 'MESSAGEBOX' con l'apposita funzione della libreria*/
		this->_alphaglobal=setter;
	}
	const Uint8 Get_AlphaLibrary(void) const{
		/*Ritorna l'alpha globale della libreria*/
		return this->_alphaglobal;
	}
	const bool Is_AlphaLibrary(void) const{
		/*Ritorna 'true' se il canale di trasparenza globale della libreria è diverso da quello NULLO*/
		if(this->_alphaglobal!=SDL_ALPHA_OPAQUE){
			return true;
		}
		return false;
	}













public:		//ACCESS SINGLETON
	inline static XGraphSettings& Get_Instance(void){
		if(XGraphSettings::prtInstance==NULL){
			XGraphSettings::prtInstance = new XGraphSettings();
			assert(XGraphSettings::prtInstance);
		}
		return *XGraphSettings::prtInstance;
	}























private:	//DATA
	Uint8 _alphaglobal;
private:	//SINGLETON
	static XGraphSettings* prtInstance;
	XGraphSettings(void);
	XGraphSettings(const XGraphSettings&);
	XGraphSettings& operator=(const XGraphSettings&);
};

#define XGRAPH_Settings XGraphSettings::Get_Instance()

#endif