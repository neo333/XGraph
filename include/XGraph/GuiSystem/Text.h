#ifndef __TEXT__GUI
#define __TEXT__GUI

#include <XGraph/GuiSystem/Image.h>
#include <XGraph/GuiSystem/Font.h>

enum XGRAP_MODE_RENDER_TEXT{
	XGRAP_MODE_RENDER_TEXT_FAST,
	XGRAP_MODE_RENDER_TEXT_QUALITY
};

class Text: public Image{
public:
	Text(const std::string& init_text =std::string(),const Color& init_color =Color()):Image(),prtFont(NULL),mode_style(XGRAP_MODE_RENDER_TEXT_FAST),mycolor(init_color),
		w_text(0),h_text(0){

	}
	Text(const Text& oth):Image(oth),prtFont(oth.prtFont),text(oth.text),mode_style(oth.mode_style),mycolor(oth.mycolor),w_text(0),h_text(0){
		this->Redering();
	}
	Text& operator=(const Text& oth){
		Image::operator=(oth);
		this->w_text=0;
		this->h_text=0;
		this->prtFont=oth.prtFont;
		this->text=oth.text;
		this->mode_style=oth.mode_style;
		this->mycolor=oth.mycolor;
		this->Redering();
		return *this;
	}



public:		//METODI SET&GET
	void Set_Font(Font& setter){
		if(this->prtFont==NULL){
			this->prtFont=&setter;
			this->Redering();
		}else{
			if(setter!=*this->prtFont){
				this->prtFont=&setter;
				this->Redering();
			}
		}
	}
	void Set_Text(const std::string& setter){
		if(setter!=this->text){
			this->text=setter;
			this->Redering();
		}
	}
	void Set_Color(const Color& setter){
		if(this->mycolor!=setter){
			this->mycolor=setter;
			this->Redering();
		}
	}
	void Set_ModeRender(const XGRAP_MODE_RENDER_TEXT setter){
		if(this->mode_style!=setter){
			this->mode_style=setter;
			this->Redering();
		}
	}

	inline const std::string& Get_Text(void) const{
		return this->text;
	}

	const Sint16 Get_Widht(void) const{
		return this->w_text;
	}
	const Sint16 Get_Height(void) const{
		return this->h_text;
	}





public:		//FUNZIONI DI SUPPORTO PUBBLICHE
	inline static const Rect Get_Size_Pixel_String(const std::string& str, Font& idfont){
		/*Ritorna la larghezza in pixel di una stringa che ha il font indicato.
			PARAMETRI:
				> const std::string& (INPUT)		->		La stringa di cui calcolare la larghezza
				> const ID_FONT&	 (INPUT)		->		L'Id font col quale verificare la stringa
			RITORNO:
				Ritorna la larghezza e l'altezza in pixel della stringa.
		I valori sono espressi rispettivamente nella larghezza e nell'altezza del rettangolo ritornato*/
		if(str.size()==0){
			return Rect(Point(),0,0);
		}
		Rect rts;
		int w_rts,h_rts;
		if(TTF_SizeText(idfont,str.c_str(),&w_rts,&h_rts)==0){
			rts.Set_W(w_rts);
			rts.Set_H(h_rts);
		}
		return rts;
	}




private:	//DATA
	Font* prtFont;
	std::string text;
	XGRAP_MODE_RENDER_TEXT mode_style;
	Color mycolor;
	Sint16 w_text;
	Sint16 h_text;

private:	//FUNZIONI DI SUPPORTO
	const bool Redering(void){
		if(this->prtFont && this->text.size()>0){
			switch(this->mode_style){
			case XGRAP_MODE_RENDER_TEXT_FAST:
				this->_intSurface=TTF_RenderText_Solid(*this->prtFont, this->text.c_str(), this->mycolor);
				break;
			case XGRAP_MODE_RENDER_TEXT_QUALITY:
				this->_intSurface=TTF_RenderText_Blended(*this->prtFont, this->text.c_str(), this->mycolor);
				break;
			default:
				this->last_error+="Text: Impossibile effettuare il redering del testo con la modalità richiesta!\n";
				return false;
			}
			int w,h;
			if(TTF_SizeText(*this->prtFont,this->text.c_str(),&w,&h)!=0){
				this->last_error+="Text: Impossibile eseguire il Redering del Testo\n";
				this->last_error+=TTF_GetError();
				this->last_error+='\n';
				return false;
			}else{
				this->SetCutArea(Rect(Point(0,0),w,h));
			}
			this->w_text=w;
			this->h_text=h;
			this->Set_Alpha(this->_alpha);
		}else{
			_intSurface.Delete();
			this->w_text=0;
			this->h_text=0;
		}
		return true;
	}

private:	//FUNZIONI DEPRECATE
	const bool Load(const std::string& pack_name, const std::string& file_name, const bool& src_keycolor=true){
		assert(false);
		return false;
	}
	const bool ResizeImage(const int& wset, const int& hset){
		assert(false);
		return false;
	}
	inline void SetCutArea(const Rect& setter =Rect()){
		Image::SetCutArea(setter);
	}
};

#endif