#include <XGraph/GuiSystem/XG_Window.h>
#include <XGraph/Resource/win_res_png.h>

const int XG_Window::w_corner =18;
const int XG_Window::h_corner =20;
Color XG_Window::ctitle_text_active = Color(0,178,144);
Color XG_Window::ctitle_text_no_active = Color(0,108,74);

const bool XG_Window::Load(XG_Container* agg){
	bool status;
	XG_Container::Load(agg);
	this->SetSize(this->w,this->h);
	status=this->UpDateRender();
	return status;
}
void XG_Window::UnLoad(void){
	XG_Container::UnLoad();
	this->render.UnLoad();
	this->w=0;
	this->h=0;
}

const bool XG_Window::UpDateRender(void){
	Uint8 _alpha_mem=this->render.Get_Alpha();
	Texture source_render;
	if(source_render.Load_fromMemory(win_res_png,win_res_png_size,true)==false){
		return false;
	}
	if(XG_Component::CompositeObjectGraphic(source_render,XG_Window::w_corner,XG_Window::h_corner,this->w,this->h,this->render)==false){
		return false;
	}
	this->render.Set_Alpha(_alpha_mem);
	return true;
}
