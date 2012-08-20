#include <XGraph/GuiSystem/XG_FontSys.h>
#include <XGraph/Resource/COPRGTL_TTF.h>
#include <XGraph/Resource/CORBEL_TTF.h>

XG_FontSys* XG_FontSys::pmInstance =NULL;
XG_FontSys::XG_FontSys(void){
	this->sysFont1.Load_From_Memory(COPRGTL_TTF,COPRGTL_TTF_size,12,XGRAPH_FONT_STYLE_NORMAL);
	this->sysFont2.Load_From_Memory(CORBEL_TTF,CORBEL_TTF_size,12,XGRAPH_FONT_STYLE_NORMAL);
}
XG_FontSys::XG_FontSys(const XG_FontSys& oth){

}
XG_FontSys& XG_FontSys::operator=(const XG_FontSys& oth){
	return *this;
}