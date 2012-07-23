#include <XGraph/GuiSystem/XG_Container.h>
#include <XGraph/GuiSystem/XG_ManagerGUI.h>

XG_Container::XG_Container(void){
	XG_ManagerGUI::Get_Instance().AddContainer_toSystem(this);
}

XG_Container::~XG_Container(void){
	XG_ManagerGUI::Get_Instance().RemoveContainer_toSystem(this);
}