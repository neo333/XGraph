#include <XGraph/GuiSystem/XG_GuiSystem.h>
#include <XGraph/InputSystem/Mouse.h>
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
			this->last_input._mouseclic.xy.Set_X(ctrlMouse.Get_X());
			this->last_input._mouseclic.xy.Set_Y(ctrlMouse.Get_Y());
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
			this->last_input._mouseclic.xy.Set_X(ctrlMouse.Get_X());
			this->last_input._mouseclic.xy.Set_Y(ctrlMouse.Get_Y());
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
			this->last_input._mouseclic.xy.Set_X(ctrlMouse.Get_X());
			this->last_input._mouseclic.xy.Set_Y(ctrlMouse.Get_Y());
		}
		this->m_middle_but=button_check;
		status=true;
	}


	return status;
}

const bool XG_GuiSystem::Run(void){
	this->_last_error.clear();
	bool status=true;

	this->UpDateAllInput();

	XG_Container* _screenpnt= &XG_Screen::Get_Instance();
	if(_screenpnt->Check_Focus(this->last_input)==true){
		_screenpnt->Exeque_Controll(this->last_input);
	}

	if(_screenpnt->Drawn_Component()==false){
		this->_last_error=_screenpnt->Get_LogError();
		return false;
	}
	return true;
}