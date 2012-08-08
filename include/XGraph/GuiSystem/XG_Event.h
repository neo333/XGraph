#ifndef __XG_EVENT__GUI
#define __XG_EVENT__GUI

#include <XGraph/GuiSystem/XG_Component.h>


template<class DATA> class XG_Event{
public:		//DEFINITION_DATA
	typedef void (*PFUN)(XG_Component*,DATA*);

public:		//COSTRUTTORE
	XG_Event(const PFUN funzione, XG_Component* caller, DATA* operand):funz_ctrl(funzione),
		_whoCaller(caller),param(operand){

	}

	const bool Exe(void){
		if(this->funz_ctrl){
			this->funz_ctrl(this->_whoCaller,this->param);
			return true;
		}
		return false;
	}
private:	//DATA
	const PFUN funz_ctrl;
	XG_Component* _whoCaller;
	DATA* param;
};

#define NEWEVENT(FUNZ,CALLER,OPERAND) XG_Event<XG_Component>(FUNZ,CALLER,OPERAND)

#endif