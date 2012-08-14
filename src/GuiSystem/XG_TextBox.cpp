#include <XGraph/GuiSystem/XG_TextBox.h>
#include <XGraph/Resource/textbox_res_png.h>

const Sint16 XG_TextBox::w_corner =10;
const Sint16 XG_TextBox::h_corner =10;
const Uint32 XG_TextBox::delay_cursore =100;

const bool XG_TextBox::Load(XG_Container* handle){
	XG_Component::Load(handle);
	this->Set_Size(this->w,this->h);
	Texture _b(1,this->data.Get_Font()->Get_H_Font());
	Image _render(_b);
	this->cursore=_render;
	return this->UpDate_Render();
}

const bool XG_TextBox::UpDate_Render(void){
	Texture _source;
	if(_source.Load_fromMemory(textbox_res_png,textbox_res_png_size,false)==false){
		this->AddError_toLOG(_source.Last_Error());
		return false;
	}
	return XG_Component::CompositeObjectGraphic(_source,XG_TextBox::w_corner,XG_TextBox::h_corner,this->w,this->h,this->render_back);
}