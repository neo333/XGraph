#ifndef __XG_MANAGER__GUI
#define __XG_MANAGER__GUI

#include <XGraph/GuiSystem/XG_Container.h>
#include <cassert>

class XG_ManagerGUI{

public:		//FUNZIONI DI GESTIONE
	const bool Draw_GUI(void){
		bool result=true;
		std::vector<XG_Container*>::iterator elem;
		for(elem=this->_contenitori_globali.begin(); elem!=this->_contenitori_globali.end(); elem++){
			if((*elem)->DrawAll()==false){
				result = false;
			}
		}
		return result;
	}






public:		//ACCESSO GLOBALE
	static XG_ManagerGUI& Get_Instance(void){
		if(XG_ManagerGUI::_mInstance==NULL){
			XG_ManagerGUI::_mInstance=new XG_ManagerGUI();
			assert(XG_ManagerGUI::_mInstance);
		}
		return *XG_ManagerGUI::_mInstance;
	}













private:	//DATA
	std::vector<XG_Container*> _contenitori_globali;






private:	//COSTRUZIONE SINGLETON
	XG_ManagerGUI(void);
	XG_ManagerGUI(const XG_ManagerGUI&);
	XG_ManagerGUI& operator=(const XG_ManagerGUI&);

	static XG_ManagerGUI* _mInstance;




private:		//FUNZIONI DI SISTEMA
	friend XG_Container::XG_Container();
	friend XG_Container::~XG_Container();
	void AddContainer_toSystem(XG_Container* _adder){
		if(_adder!=NULL){
			this->_contenitori_globali.push_back(_adder);
		}
	}
	void RemoveContainer_toSystem(XG_Container* _rem){
		std::vector<XG_Container*>::iterator elem;
		this->Find_Container_byPointer(_rem,elem);
		if(elem!=this->_contenitori_globali.end()){
			this->_contenitori_globali.erase(elem);
		}
	}



private:	//FUNZIONI DI SUPPORTO PRIVATE
	void Find_Container_byPointer(const XG_Container* _pointer, std::vector<XG_Container*>::iterator& elem_out_){
		if(_pointer!=NULL){
			for(elem_out_=this->_contenitori_globali.begin(); elem_out_ != this->_contenitori_globali.end(); elem_out_++){
				if((*elem_out_)==_pointer){
					return;
				}
			}
		}
	}
};



#define SystemGUI XG_ManagerGUI::Get_Instance()

#endif