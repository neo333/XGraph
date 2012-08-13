#ifndef __XG_BUTTON__GUI
#define __XG_BUTTON__GUI

#include <XGraph/GuiSystem/XG_Component.h>
#include <XGraph/GuiSystem/XG_Event.h>

class XG_Button: public XG_Component{
public:		//COSTRUTTORE
	XG_Button(const int w_size=0, const int h_size=0):XG_Component(),select(false){
		this->SetSize(w_size,h_size);
	}
public:		//INTERFACCIA UTENTE
	virtual const bool Load(XG_Container* adder=NULL){
		this->UnLoad();
		bool status= this->UpDateRender();
		XG_Component::Load(adder);
		return status;
	}
	virtual void UnLoad(void){
		this->render_off.UnLoad();
		this->render_on.UnLoad();
		XG_Component::UnLoad();
	}
	void SetSize(const int w_size,const int h_size){
		this->w=w_size;
		this->h=h_size;
		if(this->w < XG_Button::w_corner*2+1){
			this->w=XG_Button::w_corner*2+1;
		}
		if(this->h < XG_Button::h_corner*2+1){
			this->h=XG_Button::h_corner*2+1;
		}
		this->Set_AreaGrappableRelative(Rect(Point(0,0),this->w,this->h));
		if(this->render_on.Is_Load() || this->render_off.Is_Load()){
			this->UpDateRender();
		}
	}
	virtual const int Get_W(void) const{
		if(this->render_on.Is_Load() && this->render_off.Is_Load()){
			return this->render_off.Get_Widht();
		}else{
			return 0;
		}
	}
	virtual const int Get_H(void) const{
		if(this->render_off.Is_Load()){
			return this->render_off.Get_Height();
		}else{
			return 0;
		}
	}
	virtual void SetAlpha(const Uint8 setter){
		this->render_off.Set_Alpha(setter);
		this->render_on.Set_Alpha(setter);
	}
				// << CONTROLLO EVENTI
	void OnClic_AddControll(const XG_Event<XG_Component>& adder){
		this->operation_on_lic.push_back(adder);
	}

protected:	//DISEGNO&CONTROLLO
	virtual const bool Check_Focus(const XG_Event_Input& _event){
		if(XG_Component::Check_Focus(_event)==true){
			return true;
		}
		if(_event._mouseclic.bottone==XG_Event_Input::LEFT && XG_Component::Point_inArea(_event._mouseclic.xy,Rect(this->Get_AbsolutePosition(),this->Get_W(),this->Get_H()))&& XG_Component::Mouse_inArea(this->Get_DrawnableAreaAbsolute())){
			//clic!
			return true;
		}
		return false;
	}
	virtual void Exeque_Controll(const XG_Event_Input& _event){
		if(_event._mouseclic.bottone==XG_Event_Input::LEFT && XG_Component::Point_inArea(_event._mouseclic.xy,Rect(this->Get_AbsolutePosition(),this->Get_W(),this->Get_H()))&& XG_Component::Mouse_inArea(this->Get_DrawnableAreaAbsolute())){
			std::vector<XG_Event<XG_Component>>::iterator it;
			for(it=this->operation_on_lic.begin(); it!=this->operation_on_lic.end(); it++){
				if((*it).Exe()==false){
					this->AddError_toLOG("Impossibile eseguire un controllo sul widget specificato");
				}
			}
		}
		XG_Component::Exeque_Controll(_event);
	}
	virtual const bool Drawn_Component(void){
		if(XG_Component::Mouse_inArea(Rect(this->Get_AbsolutePosition(),this->Get_W(),this->Get_H()))==true && Mouse::Get_Instance().GetState_LeftButton()==false && XG_Component::Mouse_inArea(this->Get_DrawnableAreaAbsolute())==true && this->Object_onTop()==true){
			this->select=true;
		}else{
			this->select=false;
		}


		this->render_off.Set_Position(this->Get_AbsolutePosition());
		this->render_off.SetDrawnableArea(this->Get_DrawnableAreaAbsolute());
		this->render_on.Set_Position(this->Get_AbsolutePosition());
		this->render_on.SetDrawnableArea(this->Get_DrawnableAreaAbsolute());

		if(this->select==true){
			if(this->render_on.Drawn()==false){
				this->AddError_toLOG(this->render_on.Get_LastError());
				return false;
			}
		}else{
			if(this->render_off.Drawn()==false){
				this->AddError_toLOG(this->render_off.Get_LastError());
				return false;
			}
		}
		return true;
	}

private:	//DATA
	Image render_on;
	Image render_off;
	int w;
	int h;
	bool select;
	std::vector<XG_Event<XG_Component>> operation_on_lic;

	static int w_corner;
	static int h_corner;

private:	//FUNZIONI INTERNE DI SUPPORTO
	const bool UpDateRender(void);
};

#endif