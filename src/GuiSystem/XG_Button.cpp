#include <XGraph/GuiSystem/XG_Button.h>
#include <XGraph/Resource/button_off_res_gif.h>
#include <XGraph/Resource/button_on_res_gif.h>

const Sint16 XG_Button::w_corner =6;
const Sint16 XG_Button::h_corner =6;

const bool XG_Button::Load(void){
	if(this->Is_Load()==false){
		Texture res;
		if(res.Load_fromMemory(button_off_res_gif,button_off_res_gif_size)==false){
			this->_error=res.Last_Error();
			return false;
		}
		if(XG_Component::CompositeObjectGraphic(res,XG_Button::w_corner,XG_Button::h_corner,this->Get_W(),this->Get_H(),this->render_button_off)==false){
			this->_error="Impossibile eseguire l'algoritmo di composizione componente grafico!";
			return false;
		}

		res.Delete();
		if(res.Load_fromMemory(button_on_res_gif,button_on_res_gif_size)==false){
			this->_error=res.Last_Error();
			return false;
		}
		if(XG_Component::CompositeObjectGraphic(res,XG_Button::w_corner,XG_Button::h_corner,this->Get_W(),this->Get_H(),this->render_button_on)==false){
			this->_error="Impossibile eseguire l'algoritmo di composizione componente grafico!";
		}
	}
	this->Set_Position(this->area_button.Get_Position());
	return true;
}

