#ifndef __XG_CONTAINER__GUI
#define __XG_CONTAINER__GUI

#include <XGraph/GuiSystem/XG_Component.h>
#include <vector>

class XG_Container: public XG_Component{
public:		//COSTRUTTORE PADRE
	XG_Container(void);
	virtual ~XG_Container(void);

public:		//FUNZIONI GESTIONE WIDGETS
	virtual const bool AggiungiComponente(XG_Component* _adder){
		if(_adder!=NULL){
			this->componenti_aggregati.push_back(_adder);
			return true;
		}
		return false;
	}








private:	//DATA
	friend class XG_ManagerGUI;
	std::vector<XG_Component*> componenti_aggregati;

private:	//FUNZIONI PRIVATE
	const bool DrawAll(void){
		if(this->DrawThisComponent()==false) return false;
		bool result=true;
		std::vector<XG_Component*>::iterator elem;
		for(elem=this->componenti_aggregati.begin(); elem!=this->componenti_aggregati.end(); elem++){
			if((*elem)->DrawThisComponent()==false){
				result=false;
			}
		}
		return result;
	}

protected:	//IMPLEMENTAZIONE XG_COMPONENT
	virtual const bool DrawThisComponent(void)=0;
};

#endif