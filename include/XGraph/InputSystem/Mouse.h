#ifndef __MOUSE__IS
#define __MOUSE__IS

#include <SDL/SDL.h>
#include <cassert>
#include <vector>
#include <XGraph/GuiSystem/Image.h>

class Gestore_Input;
class XG_GuiSystem;

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
	inline static Mouse& Get_Instance(void){
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

	inline const bool GetState_LeftButton(void) const{
		return this->_bleft;
	}
	inline const bool GetState_MiddleButton(void) const{
		return this->_bmiddle;
	}
	inline const bool GetState_RightButton(void) const{
		return this->_bright;
	}
	
	inline const Clic_inPoint& Get_LastClic(void) const{
		return this->last_clic;
	}
	inline const Clic_inPoint& Get_LastClicRelease(void) const{
		return this->last_release;
	}






public:		//SKIN SETTING
	/*Setta la skin per il cursore. Inserire un parametro texture non caricato per ripristinare
	la skin di sistema*/
	void SetNormalSkin(const Texture&);













	



private:		//PRIVATE DATA
	int x;
	int y;
	bool _bleft;
	bool _bright;
	bool _bmiddle;
	Clic_inPoint last_clic;
	Clic_inPoint last_release;

	//---<<<skin>>>>----
	friend class XG_GuiSystem;
	Image skin_normal;
	bool skin_normal_loaded;
	//------------------

private:	//SINGLETON REALIZATION
	friend class Gestore_Input;
	Mouse(void);
	Mouse(const Mouse&);
	Mouse& operator=(const Mouse&);
	static Mouse* m_pInstance;
};

#define ctrlMouse Mouse::Get_Instance()

#endif