#ifndef __XG_LABEL__WIDGET
#define __XG_LABEL__WIDGET

#include <XGraph/GuiSystem/XG_Component.h>

class XG_Label: public XG_Component{
public:		//COSTRUTTORE
	XG_Label(Font& _initFont, const std::string& init_text =std::string()):XG_Component(),w_limit(0),myfont(_initFont),loaded(false),myalpha(SDL_ALPHA_OPAQUE),lines_num(0),interline(0),w_max_lines(0),mymode(XGRAP_MODE_RENDER_TEXT_QUALITY){
		this->Set_Font(_initFont);
		this->Set_Text(init_text);
	}

public:		//METODI SET&GET
	//TODO: forse è meglio verificare se i settaggi cambiano prima di effettuare re-rendering
	void Set_Text(const std::string& setter){
		this->text_extend=setter;
		this->FormatString();
	}
	void Set_Font(Font& setter){
		this->myfont=setter;
		this->FormatString();
	}
	void Set_WsizeLimit(const unsigned int setter=0){
		this->w_limit=setter;
		this->FormatString();
	}
	void Set_Color(const Color& setter){
		Iteratore it;
		for(it=this->lines.begin(); it!=this->lines.end(); it++){
			(*it).Set_Color(setter);
		}
		this->mycolor=setter;
	}
	void Set_ModeRender(const XGRAP_MODE_RENDER_TEXT setter){
		Iteratore it;
		for(it=this->lines.begin(); it!=this->lines.end(); it++){
			(*it).Set_ModeRender(setter);
		}
		this->mymode=setter;
	}
	void Set_Interline(const int setter){
		this->interline=setter;
	}

	virtual const bool Load(XG_Container* handle=NULL){
		XG_Component::Load(handle);
		this->loaded=true;
		this->FormatString();
		return true;
	}
	virtual void UnLoad(void){
		XG_Component::UnLoad();
		this->loaded=false;
		this->FormatString();
	}
	virtual const int Get_W(void) const{
		return this->w_max_lines;
	}
	virtual const int Get_H(void) const{
		return this->lines_num*(this->myfont.Get_H_Font()+this->interline);
	}
	virtual void SetAlpha(const Uint8 setter){
		Iteratore it;
		for(it=this->lines.begin(); it!=this->lines.end(); it++){
			(*it).Set_Alpha(setter);
		}
		this->myalpha=setter;
	}





protected:	//CTRL&DRAWN
	virtual const bool Check_Focus(const XG_Event_Input& _event){
		return false;
	}
	virtual void Exeque_Controll(const XG_Event_Input& _event){
		
	}
	virtual const bool Drawn_Component(void){
		Iteratore it;
		Text* ref_txt=NULL;
		int loop=0;
		bool status=true;
		for(it=this->lines.begin(); it!=this->lines.end(); it++){
			ref_txt=&(*it);

			ref_txt->Set_Position(this->Get_AbsolutePosition() + Point(0,loop*(this->myfont.Get_H_Font()+this->interline)));
			ref_txt->SetDrawnableArea(this->Get_DrawnableAreaAbsolute());

			if(ref_txt->Drawn()==false){
				status=false;
				this->AddError_toLOG(ref_txt->Get_LastError());
			}
			loop++;
		}
		return status;
	}

private:	//DATA
	typedef std::vector<Text> Paragrafo;
	typedef Paragrafo::iterator Iteratore;
	
	std::string text_extend;
	Paragrafo lines;
	unsigned int w_limit;
	Color mycolor;
	Font& myfont;
	XGRAP_MODE_RENDER_TEXT mymode;
	Uint8 myalpha;
	bool loaded;
	size_t lines_num;
	int interline;
	int w_max_lines;

private:	//INTERNAL FUNCTIONS
	void FormatString(void);
};

#endif