#ifndef __XG_WINDOW__GUI
#define __XG_WINDOW__GUI

#include <XGraph/GuiSystem/XG_Container.h>
#include <XGraph/GuiSystem/XG_FontSys.h>

class XG_Window: public XG_Container{
public:		//COSTRUTTORE
	XG_Window(const int w_size=0, const int h_size=0):XG_Container(){
		this->title_text.Set_Color(XG_Window::ctitle_text_no_active);
		this->title_text.Set_Font(XGRAPH_FONTSYS_1);
		this->title_text.Set_ModeRender(XGRAP_MODE_RENDER_TEXT_QUALITY);
		this->SetSize(w_size,h_size);
	}

	inline static XG_Window* MakeWindow(const int w_size=0, const int h_size=0){
		return new XG_Window(w_size,h_size);
	}
public:		//INTERFACCIA CONTENITORE
	virtual const bool Load(XG_Container* =NULL);	
	virtual void UnLoad(void);				
	virtual const int Get_W(void) const{
		if(this->render.Is_Load()){
			return this->render.Get_Widht();
		}
		return 0;
	}
	virtual const int Get_H(void) const{
		if(this->render.Is_Load()){
			return this->render.Get_Height();
		}
		return 0;
	}
	void SetSize(const int w_size, const int h_size){
		if(w_size==this->w && h_size==this->h) return;
		this->w=w_size;
		this->h=h_size;
		if(this->w < XG_Window::w_corner*2+1){
			this->w = XG_Window::w_corner*2+1;
		}
		if(this->h < XG_Window::h_corner*2+1){
			this->h = XG_Window::h_corner*2+1;
		}
		this->Set_AreaGrappableRelative(Rect(Point(0,0),this->w,XG_Window::h_corner));
		this->Set_ActiveAreaRelative(Rect(Point(2,XG_Window::h_corner),this->w-4,this->h-XG_Window::h_corner-3));
		if(this->render.Is_Load()){
			this->UpDateRender();
		}
	}
	virtual void SetAlpha(const Uint8 setter){
		XG_Container::SetAlpha(setter);
		this->render.Set_Alpha(setter);
	}
	void SetTextTitle(const std::string& setter){
		this->title_text.Set_Text(setter);
	}

private:	//INTERFACCIA CONTENITORE (PRIVATA)
	virtual const bool Check_Focus(const XG_Event_Input& _event){
		bool status=false;
		if(XG_Container::Check_Focus(_event)==true){
			status=true;
		}	
		if(_event._mousepress.bottone==XG_Event_Input::LEFT && XG_Component::Mouse_inArea(Rect(this->Get_AbsolutePosition(),this->Get_W(),this->Get_H()))){
			status=true;
		}
		if(_event._mouseclic.bottone==XG_Event_Input::LEFT && XG_Component::Point_inArea(_event._mouseclic.xy,Rect(this->Get_AbsolutePosition(),this->Get_W(),this->Get_H()))==true){
			status=true;
		}
		return status;
	}
	virtual const bool Drawn_Component(void){
		bool status=true;
		this->render.Set_Position(this->Get_AbsolutePosition());
		this->render.SetDrawnableArea(this->Get_DrawnableAreaAbsolute());
		this->title_text.Set_Position(this->Get_AbsolutePosition() + Point(this->Get_W()/2 - this->title_text.Get_Widht()/2,1));
		this->title_text.SetDrawnableArea(this->Get_DrawnableAreaAbsolute() - Rect(this->Get_AbsolutePosition(),this->Get_W(),XG_Window::h_corner));

		if(this->render.Drawn()==false){
			this->AddError_toLOG(this->render.Get_LastError());
			status=false;
		}

		if(this->Is_InFocus()==true){
			this->title_text.Set_Color(XG_Window::ctitle_text_active);
		}else{
			this->title_text.Set_Color(XG_Window::ctitle_text_no_active);
		}

		if(this->title_text.Drawn()==false){
			this->AddError_toLOG(this->title_text.Get_LastError());
			status=false;
		}

		if(XG_Container::Drawn_Component()==false){
			this->AddError_toLOG("XG_Contenitore: Impossibile eseguire l'operazione di disengo per i componenti aggregati\n");
			status=false;
		}
		
		return status;
	}

private:	//FUNZIONI DI SUPPORTO PRIVATE
	const bool UpDateRender(void);

private:	//DATA
	Image render;
	int w;
	int h;
	Text title_text;

	static const int w_corner;
	static const int h_corner;
	static Color ctitle_text_active;
	static Color ctitle_text_no_active;
};

#endif