#ifndef __XG_EVENT_INPUT__GUI
#define __XG_EVENT_INPUT__GUI

#include <XGraph/GuiSystem/Point.h>

class XG_Event_Input{
public:		//DEFINIZIONI
	enum TYPE_BUTTON{
		NOT,
		LEFT,
		RIGHT,
		MIDDLE
	};
	struct MOUSE_CLIC{
		TYPE_BUTTON bottone;
		Point xy;

		MOUSE_CLIC(void):bottone(NOT){

		}
	};

	struct MOUSE_BUT_PRESS{
		TYPE_BUTTON bottone;

		MOUSE_BUT_PRESS(void):bottone(NOT){

		}
	};

	struct MOUSE_BUT_RELEASE{
		TYPE_BUTTON bottone;

		MOUSE_BUT_RELEASE(void):bottone(NOT){

		}
	};

	struct KEY_PRESS{
		bool press;
		Uint16 unicode_key;
	};



public:		//DATI INPUT
	MOUSE_CLIC _mouseclic;			//EVENTO CLIC SULLO SCHERMO!
	MOUSE_BUT_PRESS _mousepress;	//EVENTO PULSANTE DEL MOUSE DOWN
	MOUSE_BUT_RELEASE _mouserel;	//EVENTO PULSANTE DEL MOUSE UP
	KEY_PRESS _key_press_instant;	//EVENTO PULSANTE TASTIERA PREMUTO

	inline void Zero(void){
		/*	Azzera l'evento in questione.
		*/
		this->_mouseclic.bottone=NOT;
		this->_mousepress.bottone=NOT;
		this->_mouserel.bottone=NOT;
		this->_key_press_instant.press=false;
	}

	inline const bool Is_Zero(void) const{
		if(this->_mouseclic.bottone!=NOT) return false;
		if(this->_mousepress.bottone!=NOT) return false;
		if(this->_mouserel.bottone!=NOT) return false;
		if(this->_key_press_instant.press==true) return false;
		return true;
	}

	operator const bool(void) const{
		if(this->Is_Zero()==true) return false;
		return true;
	}
};

#endif