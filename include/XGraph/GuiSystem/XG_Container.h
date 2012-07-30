#ifndef __XG_CONTAINER__GUI
#define __XG_CONTAINER__GUI

#include <XGraph/GuiSystem/XG_Component.h>
#include <vector>

class XG_Container: public XG_Component{
public:		//INTERFACCIA COMPONENTE GRAFICO
	virtual const bool Load(void) =0;
	virtual void UnLoad(void) =0;
	virtual void SetDrawnableArea(const Rect&) =0;
	virtual const bool Is_Load(void) const=0;
	virtual const std::string& Get_LastError(void) const{
		return this->_error;
	}
	virtual void Set_Position(const Point&) =0;
	virtual const Point& Get_Position(void) const =0;
	virtual const Sint16 Get_W(void) const =0;
	virtual const Sint16 Get_H(void) const =0;
	virtual void Set_Visible(const bool) =0;


protected:	//GESTIONE COMPONENTI AGGANCIATI
	Rect area_form_drawnable;
	std::string _error;

	void AddControll(XG_Component* adder){
		if(adder){
			this->_controlls.push_back(adder);
		}
	}
	virtual const bool DrawAndUpdate_AllControlls(void){
		std::vector<XG_Component*>::iterator it;
		for(it=this->_controlls.begin(); it!=this->_controlls.end(); it++){
			(*it)->UpDateControll();
			(*it)->SetDrawnableArea(this->area_form_drawnable);
			if((*it)->Drawn()==false){
				this->_error=(*it)->Get_LastError();
			}
		}
	}






private:	//PRIVATE DATA
	std::vector<XG_Component*> _controlls;
};

#endif