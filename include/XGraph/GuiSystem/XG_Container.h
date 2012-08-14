#ifndef __XG_CONTAINER__GUI
#define __XG_CONTAINER__GUI

#include <XGraph/GuiSystem/XG_Component.h>
#include <vector>

class XG_GuiSystem;

class XG_Container: public XG_Component{
public:			//COSTRUTTORE
	XG_Container(void):XG_Component(),is_root(false),_alphaMEM(SDL_ALPHA_OPAQUE),inFocus(false),sothing_request_focus(false),who_request_focus(NULL){
		this->active_areaRELATIVE.Set_W(Screen.Get_W_Screen());
		this->active_areaRELATIVE.Set_H(Screen.Get_H_Screen());
		this->last_widget=this->handled_component.end();
	}
private:		//NOT-COPYABLE
	XG_Container(const XG_Container& oth){
	}
	XG_Container& operator=(const XG_Container& oth){
		return *this;
	}



public:			//INTERFACCIA UTENTE
	void SetAlphaTOTAL(const Uint8 setter){
		/*Setta la trasparenza per il contenitore e anche per tutti i componenti grafici
		interni al contenitore stesso*/
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
	/*!Implementare*/virtual void SetAlpha(const Uint8 setter){
		/*	DA IMPLEMENTARE NELLA CLASSE FIGLIA!
		*/
		this->_alphaMEM=setter;
	}

	inline const bool Is_InFocus(void) const{
		return this->inFocus;
	}
	virtual void UnLoad(void){
		ITERATORE it;
		it=this->handled_component.begin();
		while(it!=this->handled_component.end()){
			(*it)->UnLoad();
			it=this->handled_component.begin();
		}
		XG_Component::UnLoad();
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

		/*
				PREPARAZIONE E CHECKFOCUS DI TUTTI GLI AGGREGATI
		*/
		REV_ITERATORE it;
		XG_Component* _current;
		this->sothing_request_focus=false;
		XG_Container* next_focus=NULL;
		bool _first=true;
		for(it=this->handled_component.rbegin(); it!=this->handled_component.rend(); it++){
			_current=(*it);

			/*preparo le posizioni e le aree di disengo*/
			if(this->is_root){
				_current->SetDrawnableAreaTOTAL(Rect(Point(0,0),OutVideo::Get_Instance().Get_W_Screen(),OutVideo::Get_Instance().Get_H_Screen()));
			}
			_current->xy_absolute_position_on_screen = this->Get_AbsolutePosition() + _current->Get_Position_Relative();
			_current->SubDrawnableAreaTOTAL(this->active_areaRELATIVE + this->Get_AbsolutePosition());
			/*---------------------------------------*/

			/*Casting*/
			XG_Container* _tryCast=XG_Container::TryCastIntoContainer_fromComponent(_current);
			if(_tryCast){
				if(_first==true){
					_tryCast->inFocus=true;
					_first=false;
				}else{
					_tryCast->inFocus=false;
				}
			}
			/**/

			/*Verifico se qualche componente necessita del focus*/
			if(this->sothing_request_focus==false && _current->Check_Focus(_event)==true && _current->visible==true){
				this->sothing_request_focus=true;
				this->who_request_focus=_current;
				next_focus=_tryCast;
				if(next_focus==NULL){
					next_focus=_current->xgContainer_handler;
				}
			}
			/*--------------------------------------------------*/
		}

		/*Porto il contenitore richiedente di focus in prima posizione nel vettore*/
		if(next_focus!=NULL){
			if(next_focus!=this->handled_component.back()){
				ITERATORE it;
				if(this->Find_Obj(next_focus,it)==true){
					XG_Component* _temp=this->handled_component.back();
					XG_Container* _cast=XG_Container::TryCastIntoContainer_fromComponent(_temp);
					assert(_cast);	//in polposition non dovrebbe essereci un object se next_focus è diverso da null
					this->handled_component.back()=next_focus;
					(*it)=_temp;
				}
			}
		}


		if(XG_Component::Check_Focus(_event)==true) return true;
		if(this->sothing_request_focus==true) return true;
		return false;
	}
	virtual void Exeque_Controll(const XG_Event_Input& _event){
		if(this->sothing_request_focus==true){
			//this->handled_component.back()->Exeque_Controll(_event);
			this->who_request_focus->Exeque_Controll(_event);
		}else{
			XG_Component::Exeque_Controll(_event);
		}
		
		//TODO: forse bisognerebbe fare che il controllo del contenitore si esegue se non ci sono controlli interni!
	}
	virtual const bool Drawn_Component(void){
		ITERATORE it;
		bool status=true;
		XG_Component* cursor;
		for(it=this->handled_component.begin(); it!=this->handled_component.end(); it++){
			cursor=(*it);
			if(cursor->visible==true){
				if(cursor->Drawn_Component()==false){
					this->AddError_toLOG(cursor->Get_LogError());
					status=false;
				}
			}
		}
		return status;
	}



private:		//GESTIONE AGGREGATI
	friend const bool XG_Component::Load(XG_Container*);
	friend void XG_Component::UnLoad(void);
	friend const bool XG_Component::Object_onTop(void) const;
	typedef std::vector<XG_Component*> LISTA_COMPONENTI;
	typedef std::vector<XG_Component*>::iterator ITERATORE;
	typedef std::vector<XG_Component*>::reverse_iterator REV_ITERATORE;

	const bool Add_Controll_toThisContainer(XG_Component* adder){
		if(adder==NULL) return false;
		XG_Container* _cast=XG_Container::TryCastIntoContainer_fromComponent(adder);
		if(_cast!=NULL){
			this->handled_component.push_back(adder);
		}else{
			this->Find_Last_Container(this->last_widget);
			this->last_widget=this->handled_component.insert(this->last_widget,adder);
		}
		return true;
	}
	void Del_Controll_toThisContainer(XG_Component* remover){
		if(remover==NULL) return;
		ITERATORE it;
		if(this->Find_Obj(remover,it)){
			XG_Container* _cast=XG_Container::TryCastIntoContainer_fromComponent(remover);
			if(_cast==NULL){
				this->last_widget=this->handled_component.erase(it);
				if(this->last_widget!=this->handled_component.begin()){
					this->last_widget--;
				}

			}else{
				this->handled_component.erase(it);
			}
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
private:		//FUNZIONI DI SUPPORTO INTERNE
	inline const bool Find_Obj(XG_Component* search, ITERATORE& _out){
		if(search==NULL) return false;
		for(_out=this->handled_component.begin(); _out!=this->handled_component.end(); _out++){
			if((*_out)==search){
				return true;
			}
		}
		return false;
	}
	inline static XG_Container* TryCastIntoContainer_fromComponent(XG_Component* obj){
		return dynamic_cast<XG_Container*>(obj);
	}
	inline const bool Find_Last_Container(ITERATORE& _out){
		REV_ITERATORE it;
		it=this->handled_component.rbegin();
		unsigned int loop=0;
		for(it=this->handled_component.rbegin(); it!=this->handled_component.rend() && XG_Container::TryCastIntoContainer_fromComponent((*it))!=NULL; it++){
			loop++;
		}

		_out=this->handled_component.begin();
		for(unsigned int i=0; i<this->handled_component.size() - loop; i++){
			_out++;
		}
		if(_out==this->handled_component.begin()) return false;
		return true;
	}

private:	//DATI INTERNI
	friend class XG_Screen;
	bool is_root;
	Rect active_areaRELATIVE;
	LISTA_COMPONENTI handled_component;
	Uint8 _alphaMEM;
	bool inFocus;
	bool sothing_request_focus;
	ITERATORE last_widget;
	XG_Component* who_request_focus;
};

#endif