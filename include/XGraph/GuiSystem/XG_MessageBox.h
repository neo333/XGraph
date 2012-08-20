#ifndef __XG_MESSAGEBOX_GUI
#define __XG_MESSAGEBOX_GUI

#include <XGraph/GuiSystem/XG_Window.h>
#include <XGraph/GuiSystem/XG_Label.h>
#include <XGraph/GuiSystem/XG_Button.h>

enum XGRAPH_MESSAGEBOX_TYPE{
	XGRAPH_MESSAGEBOX_TYPE_NORMAL,
	XGRAPH_MESSAGEBOX_TYPE_YES_NO,
	XGRAPH_MESSAGEBOX_TYPE_OK_UNDO
};

enum XGRAPH_MESSAGEBOX_RESULT{
	XGRAPH_MESSAGEBOX_RESULT_PROCESS,
	XGRAPH_MESSAGEBOX_RESULT_YES,
	XGRAPH_MESSAGEBOX_RESULT_NO
};

class XG_MessageBox: public XG_Window{
public:
	XG_MessageBox(const std::string& init_title, const std::string& init_mess, const XGRAPH_MESSAGEBOX_TYPE init_type, XGRAPH_MESSAGEBOX_RESULT* const init_result):
		XG_Window(), type(init_type), mess_data(XGRAPH_FONTSYS_1), point_result(init_result){
		
		XG_Window::Load();
		XG_Window::SetSize(480,180);
		XG_Window::SetTextTitle(init_title);
		this->Set_Position_Relative(Point(OutVideo::Get_Instance().Get_W_Screen()/2 - this->Get_W()/2,OutVideo::Get_Instance().Get_H_Screen()/2 - this->Get_H()/2));

		this->mess_data.Load(this);
		this->mess_data.Set_Position_Relative(Point(10,35));
		this->mess_data.Set_Color(Color(0,123,123));
		this->mess_data.Set_WsizeLimit(this->Get_W()-20);
		this->mess_data.Set_Text(init_mess);

		if(this->point_result){
			*this->point_result=XGRAPH_MESSAGEBOX_RESULT_PROCESS;
		}

		this->SetSize(this->Get_W(),this->mess_data.Get_H() + 80);

		switch(this->type){
		case XGRAPH_MESSAGEBOX_TYPE_NORMAL:
			this->ok.Load(this);
			this->ok.SetText("OK");
			this->ok.SetSize(120,20);
			this->ok.Set_Position_Relative(Point(this->Get_W()/2 - this->ok.Get_W()/2,this->Get_H() - this->ok.Get_H() - 10));
			this->ok.OnClic_AddControll(NEWEVENT(XG_MessageBox::CloseThisWin,&this->ok,this));
			break;
		case XGRAPH_MESSAGEBOX_TYPE_YES_NO:
			this->ok.Load(this);
			this->ok.SetText("SI");
			this->ok.SetSize(120,20);
			this->ok.Set_Position_Relative(Point(this->Get_W()/2 - this->ok.Get_W()/2 - this->ok.Get_W(),this->Get_H() - this->ok.Get_H() - 10));
			this->ok.OnClic_AddControll(NEWEVENT(XG_MessageBox::CloseThisWin_withYES,&this->ok,this));

			this->cancel.Load(this);
			this->cancel.SetText("NO");
			this->cancel.SetSize(120,20);
			this->cancel.Set_Position_Relative(Point(this->Get_W()/2 - this->cancel.Get_W()/2 + this->cancel.Get_W(),this->Get_H() - this->cancel.Get_H() - 10));
			this->cancel.OnClic_AddControll(NEWEVENT(XG_MessageBox::CloseThisWin_withNO,&this->cancel,this));
			break;
		case XGRAPH_MESSAGEBOX_TYPE_OK_UNDO:
			this->ok.Load(this);
			this->ok.SetText("OK");
			this->ok.SetSize(120,20);
			this->ok.Set_Position_Relative(Point(this->Get_W()/2 - this->ok.Get_W()/2 - this->ok.Get_W(),this->Get_H() - this->ok.Get_H() - 10));
			this->ok.OnClic_AddControll(NEWEVENT(XG_MessageBox::CloseThisWin_withYES,&this->ok,this));

			this->cancel.Load(this);
			this->cancel.SetText("ANNULLA");
			this->cancel.SetSize(120,20);
			this->cancel.Set_Position_Relative(Point(this->Get_W()/2 - this->cancel.Get_W()/2 + this->cancel.Get_W(),this->Get_H() - this->cancel.Get_H() - 10));
			this->cancel.OnClic_AddControll(NEWEVENT(XG_MessageBox::CloseThisWin_withNO,&this->cancel,this));
			break;
		}
	}
private:	//DATA
	XG_Label mess_data;
	XG_Button ok;
	XG_Button cancel;
	const XGRAPH_MESSAGEBOX_TYPE type;
	XGRAPH_MESSAGEBOX_RESULT* const point_result;

private:	//FUNZIONI
	static void CloseThisWin(XG_Component* caller, XG_Component* win){
		if(win){
			win->UnLoad();
		}
	}
	static void CloseThisWin_withYES(XG_Component* caller, XG_Component* win){
		XG_MessageBox* cast=dynamic_cast<XG_MessageBox*>(win);
		if(cast){
			if(cast->point_result){
				*cast->point_result=XGRAPH_MESSAGEBOX_RESULT_YES;
			}
			cast->UnLoad();
		}
	}
	static void CloseThisWin_withNO(XG_Component* caller, XG_Component* win){
		XG_MessageBox* cast=dynamic_cast<XG_MessageBox*>(win);
		if(cast){
			if(cast->point_result){
				*cast->point_result=XGRAPH_MESSAGEBOX_RESULT_NO;
			}
			cast->UnLoad();
		}
	}
};

#define New_MessageBox(TITLE,MESSAGE) \
			NewComponent(new XG_MessageBox(TITLE,MESSAGE,XGRAPH_MESSAGEBOX_TYPE_NORMAL,NULL));
#define New_MessageBox_plus(TITLE,MESSAGE,TYPE,RESULT_POINTER) \
			NewComponent(new XG_MessageBox(TITLE,MESSAGE,TYPE,RESULT_POINTER));

#endif