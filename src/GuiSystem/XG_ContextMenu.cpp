#include <XGraph/GuiSystem/XG_ContextMenu.h>
#include <XGraph/GuiSystem/XG_Component.h>
#include <XGraph/GuiSystem/XG_FontSys.h>
#include <XGraph/Resource/contextmenu_png.h>
#include <cassert>

const Sint16 XG_ContextMenu::w_corner =15;
const Sint16 XG_ContextMenu::h_corner =15;
const Sint16 XG_ContextMenu::interline =10;
const Color XG_ContextMenu::label_non_select =Color(0,123,123);
const Color XG_ContextMenu::label_select =XG_ContextMenu::label_non_select + Color(50,50,50);

void XG_ContextMenu::MakeRender(void){
	if(this->loaded==false){
		this->box_render.UnLoad();
		this->argomenti_render.clear();
		this->argomenti_render.reserve(this->argomenti.size());
		
		/*redering label del contextmenu*/
		VETT_STRINGS::iterator it;
		for(it=this->argomenti.begin(); it!=this->argomenti.end(); it++){
			this->argomenti_render.push_back(Text((*it),XG_ContextMenu::label_non_select));
			this->argomenti_render.back().Set_ModeRender(XGRAP_MODE_RENDER_TEXT_QUALITY);
			this->argomenti_render.back().Set_Font(XGRAPH_FONTSYS_1);
		}
		/*-----------------------*/

		/*calcolo delle dimensioni*/
		VETT_TEXT::iterator tt;
		Sint16 h_total=0;
		Sint16 w_max_labels=0;
		Sint16 w_current=0;
		for(tt=this->argomenti_render.begin(); tt!=this->argomenti_render.end(); tt++){
			w_current=(*tt).Get_Widht();
			if(w_current>w_max_labels){
				w_max_labels=w_current;
			}
			h_total+=(*tt).Get_Height();
			h_total+=XG_ContextMenu::interline;
		}
		/*-----------------------*/

		/*redering box del contextmenu*/
		Texture source;
		source.Load_fromMemory(contextmenu_png,contextmenu_png_size,false);
		bool result=XG_Component::CompositeObjectGraphic(source,XG_ContextMenu::w_corner,XG_ContextMenu::h_corner,w_max_labels+10,h_total,this->box_render);
		assert(result);
		/*----------------------------*/

		this->loaded=true;
	}
}

const bool XG_ContextMenu::Drawn(const Point& pos_drawn){
	if(this->loaded==false) this->MakeRender();
		
	this->box_render.Set_Position(pos_drawn);
		
	bool status=true;
	if(this->box_render.Drawn()==false){
		status=false;
	}

	VETT_TEXT::iterator it;
	Text* _current;
	Sint16 y_d = 0;
	for(it=this->argomenti_render.begin(); it!=this->argomenti_render.end(); it++){
		_current=&(*it);

		_current->Set_Position(pos_drawn + Point(this->Get_W()/2 - _current->Get_Widht()/2, y_d));
		y_d+=_current->Get_Height()+XG_ContextMenu::interline;

		//cambio colore di selezione
		if(XG_Component::Mouse_inArea(Rect(_current->Get_Position(),_current->Get_Widht(),_current->Get_Height()))==true){
			_current->Set_Color(XG_ContextMenu::label_select);
		}else{
			_current->Set_Color(XG_ContextMenu::label_non_select);
		}
		//

		if(_current->Drawn()==false){
			status=false;
		}
	}

	return status;
}