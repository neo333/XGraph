#include <XGraph/GuiSystem/XG_Window.h>
#include <XGraph/Resource/win_res_png.h>

const int XG_Window::w_corner =18;
const int XG_Window::h_corner =20;

const bool XG_Window::Load(XG_Container* agg){
	bool status;
	this->SetSize(this->w,this->h);
	status=this->UpDateRender();
	XG_Container::Load(agg);
	return status;
}
void XG_Window::UnLoad(void){
	XG_Container::UnLoad();
}

const bool XG_Window::UpDateRender(void){
	Texture source_render;
	if(source_render.Load_fromMemory(win_res_png,win_res_png_size,true)==false){
		return false;
	}
	if(XG_Component::CompositeObjectGraphic(source_render,XG_Window::w_corner,XG_Window::h_corner,this->w,this->h,this->render)==false){
		return false;
	}
	return true;
}
