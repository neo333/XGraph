#ifndef __XG_CONTAINER__GUI
#define __XG_CONTAINER__GUI

#include <XGraph/GuiSystem/XG_Component.h>
#include <vector>

class XG_Container: public XG_Component{
public:
	XG_Container(void);
public:		//INTERFACCIA COMPONENTE GRAFICO
	virtual void SetDrawnableArea(const Rect& setter){
		this->area_drawnable_this=setter;
	}
	virtual const Rect& GetDrawnableArea(void) const=0;
	virtual void Set_Visible(const bool setter){
		this->visible=setter;
		std::vector<XG_Component*>::iterator it;
		for(it=this->_controlls.begin(); it!=this->_controlls.end(); it++){
			(*it)->Set_Visible(this->visible);
		}
	}
	virtual const bool Run(void){
		XG_Component::Run();
		if(this->visible==true){
			bool status=true;
			std::vector<XG_Component*>::iterator it;
			Rect _inter;
			for(it=this->_controlls.begin(); it!=this->_controlls.end(); it++){
				(*it)->Set_Position((*it)->Get_Position() + this->Get_Position());
				if(Rect::Rects_Intersect(this->area_drawnable_this,this->area_form_drawnable,_inter)==true){
					(*it)->SetDrawnableArea(_inter);
					if(this->agganciato==true){
						(*it)->active_controll=false;
					}else{
						(*it)->active_controll=true;
					}
					if((*it)->Run()==false){
						this->_error+=(*it)->Get_LastError() +"\n";
						status=false;
					}
				}else{
					
				}
				(*it)->Set_Position((*it)->Get_Position() - this->Get_Position());
			}
			return status;
		}
		return true;
	}
	virtual const std::string& Get_LastError(void) const{
		return this->_error;
	}
	virtual void UnLoad(void){
		std::vector<XG_Component*>::iterator it;
		for(it=this->_controlls.begin(); it!=this->_controlls.end(); it++){
			(*it)->UnLoad();
		}
	}
	virtual const bool Load(void){
		bool status =true;
		std::vector<XG_Component*>::iterator it;
		for(it=this->_controlls.begin(); it!=this->_controlls.end(); it++){
			if((*it)->Load()==false){
				status=false;
			}
		}
		return status;
	}
protected:
	bool visible;
	virtual void UpDateControll(void) =0;
	virtual const bool Drawn(void) =0;

protected:	//GESTIONE COMPONENTI AGGANCIATI
	Rect area_form_drawnable;		//da tenere aggiornata!! ad ogni spostamento o resize (area in cui gli oggetti aggregati sono disegnabili)
	std::string _error;

	void AddControll(XG_Component* adder){
		if(adder){
			this->_controlls.push_back(adder);
		}
	}



private:	//GESTIONE BASSO LIVELLO DEI COMPONENTI AGGREGATI
	Rect area_drawnable_this;

private:	//PRIVATE DATA
	std::vector<XG_Component*> _controlls;
};

#endif