#ifndef __MOUSE__IS
#define __MOUSE__IS

#include <SDL/SDL.h>
#include <cassert>
#include <vector>

class Gestore_Input;

enum TYPE_MOUSE_BUTTON{
	TMB_NULL,
	TMB_LEFT,
	TMB_RIGHT,
	TMB_MIDDLE
};

struct Clic_inPoint{
	Sint16 x_clic;
	Sint16 y_clic;
	TYPE_MOUSE_BUTTON button_type_clic;
};

class Mouse{
public:		//ACCESS
	static Mouse& Get_Instance(void){
		if(Mouse::m_pInstance==NULL){
			Mouse::m_pInstance=new Mouse();
			assert(Mouse::m_pInstance);
		}
		return *Mouse::m_pInstance;
	}

public:		//GET REAL-TIME STATE MOUSE
	inline const int Get_X(void) const{
		return this->x;
	}
	inline const int Get_Y(void) const{
		return this->y;
	}

	const bool GetState_LeftButton(void) const{
		return this->_bleft;
	}
	const bool GetState_MiddleButton(void) const{
		return this->_bmiddle;
	}
	const bool GetState_RightButton(void) const{
		return this->_bright;
	}
	
	inline const Clic_inPoint& Get_LastClic(void) const{
		return this->last_clic;
	}
	inline const Clic_inPoint& Get_LastClicRelease(void) const{
		return this->last_release;
	}








	



private:		//PRIVATE DATA
	int x;
	int y;
	bool _bleft;
	bool _bright;
	bool _bmiddle;
	Clic_inPoint last_clic;
	Clic_inPoint last_release;

private:	//SINGLETON REALIZATION
	friend class Gestore_Input;
	Mouse(void);
	Mouse(const Mouse&);
	Mouse& operator=(const Mouse&);
	static Mouse* m_pInstance;
};

#define ctrlMouse Mouse::Get_Instance()

#endif