#include <XGraph/GuiSystem/XG_Component.h>
#include <XGraph/GuiSystem/XG_Container.h>
#include <XGraph/GuiSystem/XG_Screen.h>

/*		

	TEXTURE SORGENTE
	[SS w_corner x h_corner]		[SC	1 x h_corner]			[SD w_corner x h_corner]
	[CS w_corner x 1]				[CS 1 x 1]					[CD w_corner x 1]
	[GS w_corner x h_corner]		[GC 1 x h_corner]			[GD w_corner x h_corner]

*/
const bool XG_Component::CompositeObjectGraphic(const Texture& source, const Sint16 w_corner, const Sint16 h_corner, 
		const Sint16 w_size, const Sint16 h_size, Image& _out){
	if(source.Is_Load()==false) return false;
	

	Texture render(w_size,h_size);
	if(render.Is_Load()==false) return false;

	_out.UnLoad();
	Sint16 w_middle=w_size - (w_corner*2);
	Sint16 h_middle=h_size - (h_corner*2);
	Point xy_paste;
	Rect cut_paste;

	for(Sint16 k=0; k<h_middle+2; k++){
		for(Sint16 i=0; i<w_middle+2; i++){
			if(k==0){
				if(i==0){
					//SS
					xy_paste.Set_X(0);
					xy_paste.Set_Y(0);
					cut_paste.Set_Position(Point(0,0));
					cut_paste.Set_W(w_corner);
					cut_paste.Set_H(h_corner);
				}else{
					if(i==w_middle+1){
						//SD
						xy_paste.Set_X(w_corner + (i-1));
						xy_paste.Set_Y(0);
						cut_paste.Set_Position(Point(w_corner +1,0));
						cut_paste.Set_W(w_corner);
						cut_paste.Set_H(h_corner);
					}else{
						//SC
						xy_paste.Set_X(w_corner + (i-1));
						xy_paste.Set_Y(0);
						cut_paste.Set_Position(Point(w_corner,0));
						cut_paste.Set_W(1);
						cut_paste.Set_H(h_corner);
					}
				}
			}else{
				if(k==h_middle+1){
					if(i==0){
						//GS
						xy_paste.Set_X(0);
						xy_paste.Set_Y(h_corner + (k-1));
						cut_paste.Set_Position(Point(0,h_corner+1));
						cut_paste.Set_W(w_corner);
						cut_paste.Set_H(h_corner);
					}else{
						if(i==w_middle+1){
							//GD
							xy_paste.Set_X(w_corner + (i-1));
							xy_paste.Set_Y(h_corner + (k-1));
							cut_paste.Set_Position(Point(w_corner+1,h_corner+1));
							cut_paste.Set_W(w_corner);
							cut_paste.Set_H(h_corner);
						}else{
							//GC
							xy_paste.Set_X(w_corner + (i-1));
							xy_paste.Set_Y(h_corner + (k-1));
							cut_paste.Set_Position(Point(w_corner,h_corner+1));
							cut_paste.Set_W(1);
							cut_paste.Set_H(h_corner);
						}
					}
				}else{
					if(i==0){
						//CS
						xy_paste.Set_X(0);
						xy_paste.Set_Y(h_corner + (k-1));
						cut_paste.Set_Position(Point(0,h_corner));
						cut_paste.Set_W(w_corner);
						cut_paste.Set_H(1);
					}else{
						if(i==w_middle+1){
							//CD
							xy_paste.Set_X(w_corner + (i-1));
							xy_paste.Set_Y(h_corner + (k-1));
							cut_paste.Set_Position(Point(w_corner+1,h_corner));
							cut_paste.Set_W(w_corner);
							cut_paste.Set_H(1);
						}else{
							//CC
							xy_paste.Set_X(w_corner + (i-1));
							xy_paste.Set_Y(h_corner + (k-1));
							cut_paste.Set_Position(Point(w_corner,h_corner));
							cut_paste.Set_W(1);
							cut_paste.Set_H(1);
						}
					}
				}
			}
			render.Paste_Texture(source,xy_paste,cut_paste);
		}
	}
	_out = Image(render);
	_out.Set_ColorKey(Color(0,0,0));
	return true;
}


const bool XG_Component::Load(XG_Container* handler){
	this->UnLoad();
	this->xgContainer_handler=handler;
	if(this->xgContainer_handler==NULL){
		this->xgContainer_handler=&XG_Screen::Get_Instance();
	}
	this->xgContainer_handler->Add_Controll_toThisContainer(this);
	this->SetAlpha(this->xgContainer_handler->_alphaMEM);
	this->force_close=false;
	return true;
}

void XG_Component::UnLoad(void){
	if(this->xgContainer_handler){
		this->xgContainer_handler->Del_Controll_toThisContainer(this);
		this->xgContainer_handler=NULL;
	}
	this->force_close=true;
}

const bool XG_Component::Object_onTop(void) const{
	if(this->xgContainer_handler){
		return this->xgContainer_handler->inFocus;
	}
	return false;
}

const bool XG_Component::Drawn_Component(void){
	bool status=true;
	if(this->display_contextmenu==true){
		this->mycontextmenu.Drawn(this->xy_display_contextmenu);
	}
	return status;
}