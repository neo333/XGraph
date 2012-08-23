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
	Text(const std::string& init_text =std::string(),const Color& init_color =Color()):Image(),text(init_text),prtFont(NULL),mode_style(XGRAP_MODE_RENDER_TEXT_FAST),mycolor(init_color),
		w_text(0),h_text(0),cryp_mode(false){

	}
	Text(const Text& oth):Image(oth),prtFont(oth.prtFont),text(oth.text),mode_style(oth.mode_style),mycolor(oth.mycolor),w_text(0),h_text(0),cryp_mode(oth.cryp_mode){
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
		this->cryp_mode=oth.cryp_mode;
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
	void Set_CrypMode(const bool setter){
		if(this->cryp_mode!=setter){
			this->cryp_mode=setter;
			this->Redering();
		}
	}
	const bool Get_CrypMode(void) const{
		return this->cryp_mode;
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

	inline const Font* Get_Font(void) const{
		return this->prtFont;
	}




public:		//FUNZIONI DI SUPPORTO PUBBLICHE
	inline static const Rect Get_Size_Pixel_String(const std::string& str, const Font& idfont, const bool cry_mode =false){
		/*Ritorna la larghezza in pixel di una stringa che ha il font indicato.
			PARAMETRI:
				> const std::string& (INPUT)		->		La stringa di cui calcolare la larghezza
				> const ID_FONT&	 (INPUT)		->		L'Id font col quale verificare la stringa
				> const bool cry_mode(INPUT)		->		Indicare 'true' se si vuole la lunghezza della stringa in modalità
															 crittata ('*')
			RITORNO:
				Ritorna la larghezza e l'altezza in pixel della stringa.
		I valori sono espressi rispettivamente nella larghezza e nell'altezza del rettangolo ritornato*/
		if(str.size()==0){
			return Rect(Point(0,0),0,0);
		}
		Rect rts;
		int w_rts,h_rts;
		char* str_buffer=new char[str.size()+1];
		if(cry_mode==false){
			Text::StrCopy(str_buffer,str.c_str(),str.size()+1);
		}else{
			std::string str_temp(str);
			str_temp.replace(str_temp.begin(),str_temp.end(),str_temp.size(),'*');
			Text::StrCopy(str_buffer,str_temp.c_str(),str.size()+1);
		}
		if(TTF_SizeText(idfont.Get_Font_internal(),str_buffer,&w_rts,&h_rts)==0){
			rts.Set_W(w_rts);
			rts.Set_H(h_rts);
		}
		delete[] str_buffer;
		str_buffer=NULL;
		return rts;
	}
	
	inline static void StrCopy(char* str_dest, const char* str_source, const size_t size_buffer_dest){
#ifdef MVISUAL_STUDIO_COMPILER
		strcpy_s(str_dest,size_buffer_dest,str_source);
#else
		strcpy(str_dest,str_source);
#endif
	}



private:	//DATA
	Font* prtFont;
	std::string text;
	XGRAP_MODE_RENDER_TEXT mode_style;
	Color mycolor;
	Sint16 w_text;
	Sint16 h_text;
	bool cryp_mode;

private:	//FUNZIONI DI SUPPORTO
	const bool Redering(void){
		if(this->prtFont && this->text.size()>0){
			char* text_render=new char[this->text.size()+1];
			if(this->cryp_mode==false){
				Text::StrCopy(text_render,this->text.c_str(),this->text.size()+1);
			}else{
				std::string str_temp(this->text);
				str_temp.replace(str_temp.begin(),str_temp.end(),str_temp.size(),'*');
				Text::StrCopy(text_render,str_temp.c_str(),this->text.size()+1);
			}
			switch(this->mode_style){
			case XGRAP_MODE_RENDER_TEXT_FAST:
				this->_intSurface=TTF_RenderText_Solid(*this->prtFont, text_render, this->mycolor);
				break;
			case XGRAP_MODE_RENDER_TEXT_QUALITY:
				this->_intSurface=TTF_RenderText_Blended(*this->prtFont, text_render, this->mycolor);
				break;
			default:
				this->last_error+="Text: Impossibile effettuare il redering del testo con la modalità richiesta!\n";
				return false;
			}
			int w,h;
			if(TTF_SizeText(*this->prtFont,text_render,&w,&h)!=0){
				this->last_error+="Text: Impossibile eseguire il Redering del Testo\n";
				this->last_error+=TTF_GetError();
				this->last_error+='\n';
				delete[] text_render;
				text_render=NULL;
				return false;
			}
			this->SetCutArea(Rect(Point(0,0),w,h));
			this->w_text=w;
			this->h_text=h;
			this->Set_Alpha(this->_alpha);
			delete[] text_render;
			text_render=NULL;
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