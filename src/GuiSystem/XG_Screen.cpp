#include <XGraph/GuiSystem/XG_Screen.h>
#include <XGraph/GuiSystem/XG_GuiSystem.h>

XG_Screen* XG_Screen::mpInstance =NULL;
XG_Screen::XG_Screen(void){
	this->is_root=true;
}
XG_Screen::XG_Screen(const XG_Screen& oth){

}
XG_Screen& XG_Screen::operator=(const XG_Screen& oth){
	return *this;
}


const bool XG_Screen::Load(XG_Container* __p__){
	this->Set_ActiveAreaRelative(Rect(Point(0,0),this->Get_W(),this->Get_H()));
	return true;
}
void XG_Screen::UnLoad(void){
}