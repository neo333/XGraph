#ifndef __XG_WINDOW_CONTAINER
#define __XG_WINDOW_CONTAINER

#include <XGraph/GuiSystem/XG_Container.h>

class XG_Window: public XG_Container{
public:		//COSTRUTTORI
	XG_Window(const Sint16 SizeW, const Sint16 SizeH):XG_Container(){
		this->SetSize(SizeW,SizeH);
	}
public:		//INTERFACCIA COMPONENTE GRAFICO
	virtual const bool Load(void);
	virtual void UnLoad(void){
		this->render_win.UnLoad();
	}
	virtual void SetDrawnableArea(const Rect& setter){
		this->render_win.SetDrawnableArea(setter);
	}
	virtual const bool Is_Load(void) const{
		return this->render_win.Is_Load();
	}
	virtual void Set_Position(const Point& setter){
		this->form_win.Set_Position(setter);
		this->render_win.Set_Position(setter);
	}
	virtual const Point& Get_Position(void) const{
		this->form_win.Get_Position();
	}
	virtual const Sint16 Get_W(void) const{
		return this->form_win.Get_W();
	}
	virtual const Sint16 Get_H(void) const{
		return this->form_win.Get_H();
	}
	virtual void Set_Visible(const bool) =0;
	protected:
	virtual void UpDateControll(void){
		XG_Component::UpdateTrascinaObj(this->area_form);
	}
	virtual const bool Drawn(void){
		return this->render_win.Drawn();
	}

public:		//METODI SET&GET
	void SetSize(const Sint16 w_setter, const Sint16 h_setter){
		if(w_setter==this->form_win.Get_W() && h_setter==this->form_win.Get_H()){
			return;
		}
		this->form_win.Set_W(w_setter);
		this->form_win.Set_H(h_setter);
		if(this->form_win.Get_W()< XG_Window::w_corner*2+1){
			this->form_win.Set_W(XG_Window::w_corner*2+1);
		}
		if(this->form_win.Get_H() < XG_Window::h_corner*2+1){
			this->form_win.Set_H(XG_Window::h_corner*2+1);
		}
		if(this->Is_Load()){
			this->UnLoad();
			this->Load();
		}
	}



private:	//PRIVATE DATA
	Image render_win;
	Rect form_win;


private:	//COSTANTI DI CLASSE
	static const Sint16 w_corner;
	static const Sint16 h_corner;

};

#endif