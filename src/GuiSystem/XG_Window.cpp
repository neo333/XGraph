#include <XGraph/GuiSystem/XG_Window.h>
#include <XGraph/Resource/win_res_png.h>

/*

	[SS(w_corner x h_corner)]			[SC(1 x h_corner)]		[SD(w_corner x h_corner)]

	[CS(w_corner x 1)]					[CC(1 x 1)]				[CD(w_corner x 1)]

	[GS(w_corner x h_corner)]			[GC(1 x h_corner)]		[GD(w_corner x h_corner)]


*/
const Sint16 XG_Window::w_corner=18;
const Sint16 XG_Window::h_corner=20;

void XG_Window::UpDateMiddleSize(void){
	this->_wsize_matrix=(this->Get_Wsize() - XG_Window::w_corner*2) +2;
	this->_hsize_matrix=(this->Get_Hsize() - XG_Window::h_corner*2) +2;
	
	Texture _textdef;
	if(_textdef.Load_fromMemory(win_res_png,win_res_png_size)==false){
		//TODO: fare errore!
		assert(false);
	}

	this->compositeImages.resize(this->_wsize_matrix);
	size_t dim=this->compositeImages.size();
	for(size_t i=0; i<dim; i++){
		this->compositeImages[i].resize(this->_hsize_matrix,Image(_textdef));
	}

	this->ManagerMatrix();
}

void XG_Window::ManagerMatrix(void){
	this->Set_Size(this->pos_and_size.Get_W(),this->pos_and_size.Get_H());
	Rect _set;
	for(int i=0; i<this->_wsize_matrix; i++){
		for(int k=0; k<this->_hsize_matrix; k++){
			if(k==0){
				if(i==0){
					//SS
					_set.Set_Position(Point(0,0));
					_set.Set_W(XG_Window::w_corner);
					_set.Set_H(XG_Window::h_corner);
				}else{
					if(i==this->_wsize_matrix-1){
						//SD
						_set.Set_Position(Point(XG_Window::w_corner+1,0));
						_set.Set_W(XG_Window::w_corner);
						_set.Set_H(XG_Window::h_corner);
					}else{
						//SC
						_set.Set_Position(Point(XG_Window::w_corner,0));
						_set.Set_W(1);
						_set.Set_H(XG_Window::h_corner);
					}
				}
			}else{
				if(k==this->_hsize_matrix-1){
					if(i==0){
						//GS
						_set.Set_Position(Point(0,XG_Window::h_corner+1));
						_set.Set_W(XG_Window::w_corner);
						_set.Set_H(XG_Window::h_corner);
					}else{
						if(i==this->_wsize_matrix-1){
							//GD
							_set.Set_Position(Point(XG_Window::w_corner+1,XG_Window::h_corner+1));
							_set.Set_W(XG_Window::w_corner);
							_set.Set_H(XG_Window::h_corner);
						}else{
							//GC
							_set.Set_Position(Point(XG_Window::w_corner,XG_Window::h_corner+1));
							_set.Set_W(1);
							_set.Set_H(XG_Window::h_corner);
						}
					}
				}else{
					if(i==0){
						//CS
						_set.Set_Position(Point(0,XG_Window::h_corner));
						_set.Set_W(XG_Window::w_corner);
						_set.Set_H(1);
					}else{
						if(i==this->_wsize_matrix-1){
							//CD
							_set.Set_Position(Point(XG_Window::w_corner+1,XG_Window::h_corner));
							_set.Set_W(XG_Window::w_corner);
							_set.Set_H(1);
						}else{
							//CC
							_set.Set_Position(Point(XG_Window::w_corner,XG_Window::h_corner));
							_set.Set_W(1);
							_set.Set_H(1);
						}
					}
				}
			}
			this->compositeImages[i][k].SetCutArea(_set);
		}
	}
	this->UpdatePositionMatrix();
	this->RenderWindow();
}

void XG_Window::UpdatePositionMatrix(void){
	Point _set;
	for(int i=0; i<this->_wsize_matrix; i++){
		for(int k=0; k<this->_hsize_matrix; k++){
			if(i==0){
				_set.Set_X(0);
			}else{
				_set.Set_X(XG_Window::w_corner + i -1);
			}

			if(k==0){
				_set.Set_Y(0);
			}else{
				_set.Set_Y(XG_Window::h_corner + k -1);
			}

			this->compositeImages[i][k].Set_Position(this->Get_Position() + _set);
		}
	}
}

void XG_Window::SetDrawnableArea(const Rect& setter){
	for(int i=0; i<this->_wsize_matrix; i++){
		for(int k=0; k<this->_hsize_matrix; k++){
			this->compositeImages[i][k].SetDrawnableArea(setter);
		}
	}
}

void XG_Window::RenderWindow(void){
	/*this->UpDateMiddleSize();
	this->UpdatePositionMatrix();


	Texture _buffer = SDL_CreateRGBSurface(SDL_HWSURFACE | SDL_SRCCOLORKEY | SDL_SRCALPHA, this->Get_Wsize(), this->Get_Hsize(), Screen.Get_BitPerPixel_Depth() , 0x00ff0000, 0x0000ff00, 0x000000ff, 0x00000000);
	Image* _temp;
	SDL_Rect pos;
	SDL_Rect cut;
	for(int i=0; i<this->_wsize_matrix; i++){
		for(int k=0; k<this->_hsize_matrix; k++){
			_temp=&this->compositeImages[i][k];
			pos.x=_temp->Get_Position().Get_X();
			pos.y=_temp->Get_Position().Get_Y();
			cut.x=_temp->GetCutArea().Get_Position().Get_X();
			cut.y=_temp->GetCutArea().Get_Position().Get_Y();
			cut.w=_temp->GetCutArea().Get_W();
			cut.h=_temp->GetCutArea().Get_H();
			SDL_BlitSurface(_temp->Get_SDLSurface(), &cut, _buffer, &pos);
		}
	}
	this->_renderized=_buffer;*/

	Texture render_texture = SDL_CreateRGBSurface(SDL_HWSURFACE | SDL_SRCCOLORKEY | SDL_SRCALPHA, this->Get_Wsize(), this->Get_Hsize(), Screen.Get_BitPerPixel_Depth() , 0x00ff0000, 0x0000ff00, 0x000000ff, 0x00000000);
	Texture _textdef;
	if(_textdef.Load_fromMemory(win_res_png,win_res_png_size)==false){
		//TODO: fare errore!
		assert(false);
	}


}