#include <XGraph/GuiSystem/XG_Window.h>
#include <XGraph/Resource/win_res_png.h>

const Sint16 XG_Window::w_corner =18;
const Sint16 XG_Window::h_corner =20;

/*

	[SS(w_corner x h_corner)]			[SC(1 x h_corner)]		[SD(w_corner x h_corner)]

	[CS(w_corner x 1)]					[CC(1 x 1)]				[CD(w_corner x 1)]

	[GS(w_corner x h_corner)]			[GC(1 x h_corner)]		[GD(w_corner x h_corner)]


*/

const bool XG_Window::Load(void){
	if(this->Is_Load()==false){
		Texture res;
		res.Load_fromMemory(win_res_png,win_res_png_size);
		if(XG_Component::CompositeObjectGraphic(res,XG_Window::w_corner,XG_Window::h_corner,this->Get_W(),this->Get_H(),this->render_win)==false){
			this->_error="Impossibile eseguire l'algoritmo di composizione componente grafico!";
			return false;
		}
	}
	return true;
}