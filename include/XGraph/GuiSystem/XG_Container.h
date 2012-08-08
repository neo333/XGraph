#ifndef __XG_CONTAINER__GUI
#define __XG_CONTAINER__GUI

#include <XGraph/GuiSystem/XG_Component.h>
#include <vector>

class XG_GuiSystem;

class XG_Container: public XG_Component{
public:			//COSTRUTTORE
	XG_Container(void):XG_Component(),is_root(false),_alphaMEM(SDL_ALPHA_OPAQUE){
		this->active_areaRELATIVE.Set_W(Screen.Get_W_Screen());
		this->active_areaRELATIVE.Set_H(Screen.Get_H_Screen());
	}
private:		//NOT-COPYABLE
	XG_Container(const XG_Container& oth){
	}
	XG_Container& operator=(const XG_Container& oth){
		return *this;
	}



public:			//INTERFACCIA UTENTE
	void SetAlphaTOTAL(const Uint8 setter){
		this->SetAlpha(setter);
		ITERATORE it;
		XG_Component* _current;
		for(it=this->handled_component.begin(); it!=this->handled_component.end(); it++){
			_current=(*it);
			XG_Container* _tecon = dynamic_cast<XG_Container*>(_current);
			if(_tecon){
				_tecon->SetAlphaTOTAL(setter);
			}else{
				_current->SetAlpha(setter);
			}
		}
	}
	virtual void SetAlpha(const Uint8 setter){
		/*	RICORDATI DI RICHIAMARE QUESTA FUNZIONE NELLA CLASSE FIGLIA!
		*/
		this->_alphaMEM=setter;
	}





protected:		//INTERFACCIA INTERNA
	inline void Set_ActiveAreaRelative(const Rect& setter){		//l'active area è l'area del contenitore
		this->active_areaRELATIVE=setter;						//dove possono essere visualizzati i componenti graficia aggregati
																//questa funzione andrebbe richiamata ad ogni dimensionamento
																//dell'oggetto!
														
	}
	
protected:		//INTERFACCIA COMPONTENT CONTRLL & DISEGNO
	friend class XG_GuiSystem;
	virtual const bool Check_Focus(const XG_Event_Input& _event){
		this->RunContainer(_event);
		if(XG_Component::Check_Focus(_event)==true) return true;
		if(this->request_focus_component){
			return true;
		}
		return false;
	}
	virtual void Exeque_Controll(const XG_Event_Input& _event){
		XG_Component::Exeque_Controll(_event);
		if(this->request_focus_component){
			this->request_focus_component->Exeque_Controll(_event);
		}
		//TODO: forse bisognerebbe fare che il controllo del contenitore si esegue se non ci sono controlli interni!
	}
	virtual const bool Drawn_Component(void){
		ITERATORE it;
		bool status=true;
		for(it=this->handled_component.begin(); it!=this->handled_component.end(); it++){
			if((*it)->visible==true){
				if((*it)->Drawn_Component()==false){
					this->AddError_toLOG((*it)->Get_LogError());
					status=false;
				}
			}
		}
		return status;
	}



private:		//GESTIONE AGGREGATI
	friend const bool XG_Component::Load(XG_Container*);
	friend void XG_Component::UnLoad(void);
	typedef std::vector<XG_Component*> LISTA_COMPONENTI;
	typedef std::vector<XG_Component*>::iterator ITERATORE;

	const bool Add_Controll_toThisContainer(XG_Component* adder){
		if(adder==NULL) return false;
		this->handled_component.push_back(adder);
		return true;
	}
	void Del_Controll_toThisContainer(XG_Component* remover){
		ITERATORE it;
		if(this->Find_Obj(remover,it)){
			this->handled_component.erase(it);
		}
	}

	virtual void SetDrawnableAreaTOTAL(const Rect& setter){
		XG_Component::SetDrawnableAreaTOTAL(setter);
		ITERATORE it;
		for(it=this->handled_component.begin(); it!=this->handled_component.end(); it++){
			(*it)->SetDrawnableAreaTOTAL(setter);		
		}
	}

	virtual void SubDrawnableAreaTOTAL(const Rect& setter){
		XG_Component::SubDrawnableAreaTOTAL(setter);
		ITERATORE it;
		for(it=this->handled_component.begin(); it!=this->handled_component.end(); it++){
			(*it)->SubDrawnableAreaTOTAL(setter);		
		}
	}

	void RunContainer(const XG_Event_Input& _eventIN){
		/*
				PREPARAZIONE E CHECKFOCUS DI TUTTI GLI AGGREGATI
		*/
		ITERATORE it;
		this->request_focus_component=NULL;
		XG_Component* _current;
		for(it=this->handled_component.begin(); it!=this->handled_component.end(); it++){
			_current=(*it);
			if(this->is_root){
				_current->SetDrawnableAreaTOTAL(Rect(Point(0,0),OutVideo::Get_Instance().Get_W_Screen(),OutVideo::Get_Instance().Get_H_Screen()));
			}
			_current->xy_absolute_position_on_screen = this->Get_AbsolutePosition() + _current->Get_Position_Relative();
			_current->SubDrawnableAreaTOTAL(this->active_areaRELATIVE + this->Get_AbsolutePosition());
			if(_current->Check_Focus(_eventIN)==true && _current->visible==true){
				this->request_focus_component=_current;
			}
		}
	}
private:		//FUNZIONI DI SUPPORTO INTERNE
	inline const bool Find_Obj(XG_Component* search, ITERATORE& _out){
		for(_out=this->handled_component.begin(); _out!=this->handled_component.end(); _out++){
			if((*_out)==search){
				return true;
			}
		}
		return false;
	}

private:	//DATI INTERNI
	friend class XG_Screen;
	bool is_root;
	Rect active_areaRELATIVE;
	XG_Component* request_focus_component;
	LISTA_COMPONENTI handled_component;
	Uint8 _alphaMEM;
};

#endif