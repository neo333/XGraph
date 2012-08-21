#include <XGraph/GuiSystem/XGraphSettings.h>

XGraphSettings* XGraphSettings::prtInstance =NULL;
XGraphSettings::XGraphSettings(void){
	this->DefaultSetting();
}
XGraphSettings::XGraphSettings(const XGraphSettings& oth){

}
XGraphSettings& XGraphSettings::operator=(const XGraphSettings& oth){
	return *this;
}

void XGraphSettings::DefaultSetting(void){
	this->_alphaglobal=SDL_ALPHA_OPAQUE;
}