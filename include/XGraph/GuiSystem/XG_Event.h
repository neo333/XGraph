#ifndef __XG_EVENT__GUI
#define __XG_EVENT__GUI

#include <XGraph/GuiSystem/XG_Component.h>


template<class DATA> class XG_Event{
public:		//COSTRUTTORE
	XG_Event(void (*funzione)(XG_Component*, DATA*), XG_Component* caller, DATA* operand):funz_ctrl(funzione),_whoCaller(caller),param(operand){

	}

	const bool Exe(void){
		if(this->funz_ctrl){
			this->funz_ctrl(this->_whoCaller,this->param);
			return true;
		}
		return false;
	}
private:	//DATA
	void (*funz_ctrl)(XG_Component*, DATA*);
	XG_Component* _whoCaller;
	DATA* param;
};



#endif
