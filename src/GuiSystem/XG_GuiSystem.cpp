#include <XGraph/GuiSystem/XG_GuiSystem.h>
#include <XGraph/InputSystem/Mouse.h>
#include <XGraph/InputSystem/Tastiera.h>
#include <XGraph/GuiSystem/XG_Screen.h>

XG_GuiSystem* XG_GuiSystem::mpInstance =NULL;
XG_GuiSystem::XG_GuiSystem(void):m_left_but(false), m_right_but(false), m_middle_but(false){

}
XG_GuiSystem::XG_GuiSystem(const XG_GuiSystem& oth){

}
XG_GuiSystem& XG_GuiSystem::operator=(const XG_GuiSystem& oth){
	return *this;
}

const bool XG_GuiSystem::UpDateAllInput(void){
	this->last_input.Zero();

	bool status=false;
	bool button_check;
	
	//CTRL_MOUSE BUTTON LEFT
	button_check=ctrlMouse.GetState_LeftButton();
	if(button_check!=this->m_left_but){
		if(button_check==true){
			this->last_input._mousepress.bottone=XG_Event_Input::LEFT;
		}else{
			this->last_input._mouserel.bottone=XG_Event_Input::LEFT;
			this->last_input._mouseclic.bottone=XG_Event_Input::LEFT;
			this->last_input._mouseclic.xy.Set_X(ctrlMouse.Get_LastClic().x_clic);
			this->last_input._mouseclic.xy.Set_Y(ctrlMouse.Get_LastClic().y_clic);
		}
		this->m_left_but=button_check;
		status=true;
	}

	//CTRL_MOUSE BUTTON RIGHT
	button_check=ctrlMouse.GetState_RightButton();
	if(button_check!=this->m_right_but){
		if(button_check==true){
			this->last_input._mousepress.bottone=XG_Event_Input::RIGHT;
		}else{
			this->last_input._mouserel.bottone=XG_Event_Input::RIGHT;
			this->last_input._mouseclic.bottone=XG_Event_Input::RIGHT;
			this->last_input._mouseclic.xy.Set_X(ctrlMouse.Get_LastClic().x_clic);
			this->last_input._mouseclic.xy.Set_Y(ctrlMouse.Get_LastClic().y_clic);
		}
		this->m_right_but=button_check;
		status=true;
	}

	//CTRL_MOUSE BUTTON MIDDLE
	button_check=ctrlMouse.GetState_MiddleButton();
	if(button_check!=this->m_middle_but){
		if(button_check==true){
			this->last_input._mousepress.bottone=XG_Event_Input::MIDDLE;
		}else{
			this->last_input._mouserel.bottone=XG_Event_Input::MIDDLE;
			this->last_input._mouseclic.bottone=XG_Event_Input::MIDDLE;
			this->last_input._mouseclic.xy.Set_X(ctrlMouse.Get_LastClic().x_clic);
			this->last_input._mouseclic.xy.Set_Y(ctrlMouse.Get_LastClic().y_clic);
		}
		this->m_middle_but=button_check;
		status=true;
	}

	//UPDATE KEY
	Uint16 __key;
	if(Tastiera::Get_Instance().Get_charBuffer(__key)==true){
		this->last_input._key_press_instant.press=true;
		this->last_input._key_press_instant.unicode_key=__key;
	}

	return status;
}

const bool XG_GuiSystem::Run(void){
	this->_last_error.clear();

	this->UpDateAllInput();

	this->CheckDynamicComponent();

	XG_Container* _screenpnt= &XG_Screen::Get_Instance();
	if(_screenpnt->Check_Focus(this->last_input)==true){
		_screenpnt->Exeque_Controll(this->last_input);
	}

	if(_screenpnt->Drawn_Component()==false){
		this->_last_error=_screenpnt->Get_LogError();
		return false;
	}

	if(Mouse::Get_Instance().skin_normal_loaded==true && (Mouse::Get_Instance().mode_load==false || Mouse::Get_Instance().skin_load_loaded==false)){
		Mouse::Get_Instance().skin_normal.Drawn();
	}else{
		if(Mouse::Get_Instance().mode_load==true && Mouse::Get_Instance().skin_load_loaded==true){
			Mouse::Get_Instance().skin_load.Drawn();
		}
	}

	return true;
}

void XG_GuiSystem::CheckDynamicComponent(void){
	ITERATORE_DINAMICI it;
	for(it=this->dynamic_component.begin(); it!=this->dynamic_component.end(); it++){
		if((*it).first->force_close==true){
			delete (*it).first;
			this->dynamic_component.erase(it);
		}
	}
}
