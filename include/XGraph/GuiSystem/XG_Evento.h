#ifndef __EVENTO__XG__GUI
#define __EVENTO__XG__GUI

#include <XGraph/GuiSystem/XG_Component.h>

template<class Data =XG_Component>class XG_Evento{
public:		//COSTRUTTORI
	XG_Evento(const std::string& name, void (*func_init)(Data*), Data* parametri):name_event(name),_pevent(func_init), _parametri(parametri){

	}

public:		//GESTIONE EVENTO
	void ExequeEvent(void){
		if(this->_pevent!=NULL){
			this->_pevent(this->_parametri);
		}
	}





public:		//METODI GET&SET
	const std::string& Get_NameEvent(void) const{
		return this->name_event;
	}



private:	//DATA PRIVATE
	void (*_pevent)(Data*);
	Data* _parametri;
	std::string name_event;
};

#endif