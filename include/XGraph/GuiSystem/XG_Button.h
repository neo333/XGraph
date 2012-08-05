#ifndef __XG_BUTTON_WIDGETS
#define __XG_BUTTON_WIDGETS

#include <XGraph/GuiSystem/XG_Widget.h>
#include <vector>

class XG_Button: public XG_Widget{
public:		//COSTRUTTORI
	XG_Button(const Sint16 w_size =100, const Sint16 h_size =25):XG_Widget(),select(false){
		this->SetSize(w_size,h_size);
	}




public:		//INTERFACCIA COMPONENTE GRAFICO
	virtual const bool Load(void);
	virtual void UnLoad(void){
		this->render_button_off.UnLoad();
		this->render_button_on.UnLoad();
	}
	virtual void SetDrawnableArea(const Rect& setter){
		this->render_button_off.SetDrawnableArea(setter);
		this->render_button_on.SetDrawnableArea(setter);
	}
	virtual const Rect& GetDrawnableArea(void) const{
		return this->render_button_off.GetDrawnableArea();
	}
	virtual const bool Is_Load(void) const{
		if(this->render_button_off.Is_Load()==true && this->render_button_on.Is_Load()==true){
			return true;
		}
		return false;
	}
	virtual const std::string& Get_LastError(void) const{
		return this->_error;
	}
	virtual void Set_Alpha(const Uint8 setter){
		this->render_button_off.Set_Alpha(setter);
		this->render_button_on.Set_Alpha(setter);
	}
	virtual void Set_Position(const Point& setter){
		this->area_button.Set_Position(setter);
		this->render_button_on.Set_Position(setter);
		this->render_button_off.Set_Position(setter);
		this->Set_GrappableArea(Rect(Point(0,0),this->Get_W(),this->Get_H()));
	}
	virtual const Point& Get_Position(void) const{
		return this->area_button.Get_Position();
	}
	virtual const Sint16 Get_W(void) const{
		return this->area_button.Get_W();
	}
	virtual const Sint16 Get_H(void) const{
		return this->area_button.Get_H();
	}
protected:
	virtual const bool Drawn(void){
		if(this->select==true){
			if(this->render_button_on.Drawn()==false){
				this->_error=this->render_button_on.Get_LastError();
				return false;
			}
		}else{
			if(this->render_button_off.Drawn()==false){
				this->_error=this->render_button_off.Get_LastError();
				return false;
			}
		}
		return true;
	}
	virtual void UpDateControll(void){
		if(XG_Component::Mouse_inArea(this->area_button)==true && ctrlMouse.Get_Instance().GetState_LeftButton()==false){
			this->select=true;
		}else{
			this->select=false;
		}
	}




public:		//METODI SET&GET
	void SetSize(const Sint16 w_setter, const Sint16 h_setter){
		if(w_setter==this->area_button.Get_W() && h_setter==this->area_button.Get_H()){
			return;
		}
		this->area_button.Set_W(w_setter);
		this->area_button.Set_H(h_setter);
		if(this->area_button.Get_W()< XG_Button::w_corner*2+1){
			this->area_button.Set_W(XG_Button::w_corner*2+1);
		}
		if(this->area_button.Get_H() < XG_Button::h_corner*2+1){
			this->area_button.Set_H(XG_Button::h_corner*2+1);
		}
		if(this->Is_Load()){
			this->UnLoad();
			this->Load();
		}
		this->Set_GrappableArea(Rect(Point(0,0),this->Get_W(),this->Get_H()));
	}



public:		//FUNZIONI PER EVENTI
	void OnClic_AddEvent(const XG_Evento<>& adder){
		this->eventi_on_clic.push_back(adder);
	}
	void OnClic_ClearAllEvents(void){
		this->eventi_on_clic.clear();
	}













private:	//INTERNAL DATA
	Image render_button_off;
	Image render_button_on;
	Rect area_button;
	std::string _error;
	bool select;

	std::vector<XG_Evento<>> eventi_on_clic;

private:	//STATIC VARIABLES
	static const Sint16 w_corner;
	static const Sint16 h_corner;
};

#endif