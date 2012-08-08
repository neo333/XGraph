#include <XGraph/GuiSystem/XG_Button.h>
#include <XGraph/Resource/button_off_res_gif.h>
#include <XGraph/Resource/button_on_res_gif.h>

int XG_Button::w_corner =6;
int XG_Button::h_corner =6;

const bool XG_Button::UpDateRender(void){
	Texture source;
	if(source.Load_fromMemory(button_off_res_gif,button_off_res_gif_size,true)==false){
		this->AddError_toLOG(source.Last_Error());
		return false;
	}
	if(XG_Component::CompositeObjectGraphic(source,XG_Button::w_corner,XG_Button::h_corner,this->w,this->h,this->render_off)==false){
		this->AddError_toLOG("Impossibile eseguire la composizione del componente grafico");
		return false;
	}

	source.Delete();
	if(source.Load_fromMemory(button_on_res_gif,button_on_res_gif_size,true)==false){
		this->AddError_toLOG(source.Last_Error());
		return false;
	}
	if(XG_Component::CompositeObjectGraphic(source,XG_Button::w_corner,XG_Button::h_corner,this->w,this->h,this->render_on)==false){
		this->AddError_toLOG("Impossibile eseguire la composizione del componente grafico");
		return false;
	}

	return true;
}