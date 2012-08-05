#ifndef __XG_WINDOW_CONTAINER
#define __XG_WINDOW_CONTAINER

#include <XGraph/GuiSystem/XG_Container.h>

class XG_Window: public XG_Container{
public:		//COSTRUTTORI
	XG_Window(const Sint16 SizeW, const Sint16 SizeH){
		this->SetSize(SizeW,SizeH);
		this->Set_Visible(true);
		this->Set_Moveable(true);
	}
public:		//INTERFACCIA COMPONENTE GRAFICO
	virtual const bool Load(void);
	virtual void UnLoad(void){
		XG_Container::UnLoad();
		this->render_win.UnLoad();
	}
	virtual void SetDrawnableArea(const Rect& setter){
		XG_Container::SetDrawnableArea(setter);
		this->render_win.SetDrawnableArea(setter);
		this->Set_GrappableArea(Rect(Point(0,0),this->Get_W(),XG_Window::h_corner));
	}
	virtual const Rect& GetDrawnableArea(void) const{
		return this->render_win.GetDrawnableArea();
	}
	virtual const bool Is_Load(void) const{
		return this->render_win.Is_Load();
	}
	virtual void Set_Position(const Point& setter){
		this->form_win.Set_Position(setter);
		this->render_win.Set_Position(setter);

		this->UpDateAreaActive(Rect(this->Get_Position() + Point(3,XG_Window::h_corner),this->Get_W()-6,this->Get_H()-XG_Window::h_corner-3));
		this->Set_GrappableArea(Rect(Point(0,0),0,XG_Window::h_corner));
	}
	virtual void Set_Alpha(const Uint8 setter){
		this->render_win.Set_Alpha(setter);
	}
	virtual const Point& Get_Position(void) const{
		return this->form_win.Get_Position();
	}
	virtual const Sint16 Get_W(void) const{
		return this->form_win.Get_W();
	}
	virtual const Sint16 Get_H(void) const{
		return this->form_win.Get_H();
	}
	protected:
	virtual void UpDateControll(void){

	}
	virtual const bool Drawn(void){
		if(this->visible && this->Is_Load()==true){
			return this->render_win.Drawn();
		}
		return true;
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

		this->UpDateAreaActive(Rect(this->Get_Position() + Point(3,XG_Window::h_corner),this->Get_W()-6,this->Get_H()-XG_Window::h_corner-3));
		this->Set_GrappableArea(Rect(Point(0,0),this->Get_W(),XG_Window::h_corner));
	}



private:	//PRIVATE DATA
	Image render_win;
	Rect form_win;

private:	//FUNZIONI PRIVATE
	inline void UpDateAreaActive(const Rect& setter){
		this->area_form_drawnable=setter;
	}

private:	//COSTANTI DI CLASSE
	static const Sint16 w_corner;
	static const Sint16 h_corner;
};

#endif