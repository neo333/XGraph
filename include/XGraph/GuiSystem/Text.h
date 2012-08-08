#ifndef __TEXT__GUI
#define __TEXT__GUI

#include <XGraph/GuiSystem/Image.h>
#include "Gestore_Fonts.h"

enum MODE_RENDER{
	MR_FAST,
	MR_QUALITY
};

class Text: public Image{
private:	//data
	std::string _int_text;
	ID_FONT id_punt_font;
	MODE_RENDER _mode;
	Color _color_text;
	Sint16 w_pixel_text;
	Sint16 h_pixel_text;

private:	//funzioni interne
	const bool UpDate_Render(void){
		if(this->_int_text.size()>0){
			Font* pfont=sysFonts.Get_Font_toList(this->id_punt_font);
			if(pfont==NULL){
				this->last_error="Text: Impossibile effettuare il redering del testo con il font specificato!";
				return false;
			}
			switch(this->_mode){
			case MR_FAST:
				this->_intSurface=TTF_RenderText_Solid(*pfont, this->_int_text.c_str(), this->_color_text);
				break;
			case MR_QUALITY:
				this->_intSurface=TTF_RenderText_Blended(*pfont, this->_int_text.c_str(), this->_color_text);
				break;
			default:
				this->last_error="Text: Impossibile effettuare il redering del testo con la modalità richiesta!";
				return false;
				break;
			}
			if(this->_intSurface.Is_Load()==false){
				this->last_error="Text: Impossibile eseguire il Redering del Testo\n";
				this->last_error+=TTF_GetError();
				return false;
			}
			int w,h;
			if(TTF_SizeText(*pfont,this->_int_text.c_str(),&w,&h)!=0){
				this->last_error="Text: Impossibile determinare i parametri 'size'";
				this->last_error+=TTF_GetError();
				return false;
			}
			this->w_pixel_text=(Sint16)w;
			this->h_pixel_text=(Sint16)h;
			if(this->_alpha!=SDL_ALPHA_OPAQUE){
				if(Image::Set_Alpha(this->_alpha)==false){
					return false;
				}
			}
			this->area_cut=Rect(Point(0,0),this->w_pixel_text,this->h_pixel_text);
		}else{
			this->_intSurface.Delete();
		}
		
		return true;
	}

private:	//funzioni deprecate
	const bool Load(const std::string& pack_name, const std::string& file_name, const bool& src_keycolor=true){
		assert(false);
		return false;
	}
	const bool ResizeImage(const int& wset, const int& hset){
		assert(false);
		return false;
	}
	void SetCutArea(const Rect& setter =Rect()){
		Image::SetCutArea(setter);
		assert(false);
	}
public:	//COSTRUTTORI
	Text(const ID_FONT& i_id,const MODE_RENDER& i_mode=MR_FAST):id_punt_font(i_id),w_pixel_text(0),h_pixel_text(0),_mode(i_mode){

	}

public:	//METODI setter & getter
	void Set_Text(const std::string& setter){
		if(this->_int_text!=setter){
			this->_int_text=setter;
			this->UpDate_Render();
		}
	}
	void Set_Font(const ID_FONT& setter){
		if(this->id_punt_font!=setter){
			this->id_punt_font=setter;
			this->UpDate_Render();
		}
	}
	void Set_Color(const Color& setter){
		if(this->_color_text!=setter){
			this->_color_text=setter;
			this->UpDate_Render();
		}
	}
	void Set_ModeRendering(const MODE_RENDER& setter){
		this->_mode=setter;
		this->UpDate_Render();
	}

	const std::string& Get_Text(void) const{
		return this->_int_text;
	}
	const ID_FONT& Get_Font(void) const{
		return this->id_punt_font;
	}
	const Color& Get_Color(void) const{
		return this->_color_text;
	}
	const MODE_RENDER& Get_ModeRedering(void) const{
		return this->_mode;
	}
	const Sint16& Get_W_PixelText(void) const{
		return this->w_pixel_text;
	}
	const Sint16& Get_H_PixelText(void) const{
		return this->h_pixel_text;
	}

public:		//FUNZIONI AGGIUNTIVE
	/*Ritorna la larghezza in pixel di una stringa che ha il font caricato dall'oggetto chiamante.
	PARAMETRI:
		> const std::string& (INPUT)		->		La stringa di cui calcolare la larghezza
	RITORNO:
		Ritorna la larghezza in pixel della stringa caricata col font dell'oggetto chiamante*/
	const Sint16 Get_W_Pixel_String(const std::string& str){
		if(str.size()==0){
			return 0;
		}
		int w_rts,h_rts;
		if(TTF_SizeText(*sysFonts.Get_Font_toList(this->id_punt_font),str.c_str(),&w_rts,&h_rts)!=0){
			return 0;
		}
		return (Sint16)(w_rts);
	}

	/*Ritorna la larghezza in pixel di una stringa che ha il font indicato.
	PARAMETRI:
		> const std::string& (INPUT)		->		La stringa di cui calcolare la larghezza
		> const ID_FONT&	 (INPUT)		->		L'Id font col quale verificare la stringa
	RITORNO:
		Ritorna la larghezza e l'altezza in pixel della stringa.
		I valori sono espressi rispettivamente nella larghezza e nell'altezza del rettangolo ritornato*/
	static const Rect Get_W_Pixel_String(const std::string& str, const ID_FONT& idfont){
		if(str.size()==0){

		}
		Rect rts;
		Font* pFont=sysFonts.Get_Font_toList(idfont);
		if(pFont){
			int w_rts,h_rts;
			if(TTF_SizeText(*pFont,str.c_str(),&w_rts,&h_rts)==0){
				rts.Set_W(w_rts);
				rts.Set_H(h_rts);
			}
		}
		return rts;
	}

	/*Ritorna l'altezza in pixel di un font.
	Interpretabile come l'altezza massima di tutti i possibili caratteri del font*/
	static const Sint16 Get_H_Pixel_Font(const ID_FONT& idfont){
		Font* pFont=sysFonts.Get_Font_toList(idfont);
		if(pFont){
			return TTF_FontHeight(*pFont);
		}
		return 0;
	}
public:	//overriding
	const bool Set_Alpha(const Uint8& setter){
		this->_alpha=setter;
		return Image::Set_Alpha(setter);
	}
	const bool Drawn(void){
		if(this->last_error.size()>0){
			return false;
		}
		return Image::Drawn();
	}
};



#endif