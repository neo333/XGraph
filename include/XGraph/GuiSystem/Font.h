#ifndef __FONT__COREGUI
#define __FONT__COREGUI

#include <SDL/SDL_ttf.h>
#include <string>

enum XGRAPH_FONT_STYLE{
	XGRAPH_FONT_STYLE_NOTSET,
	XGRAPH_FONT_STYLE_NORMAL,
	XGRAPH_FONT_STYLE_BOLD
};

class Font{
public:		//COSTRUZIONE E DISTRUZIONE OGGETTO
	Font(void):prtFont(NULL),load_memory_rm(NULL),size_memory_rm(0),size_rm(-1),style_rm(XGRAPH_FONT_STYLE_NORMAL),h_font(0){

	}
	
	/*WARNING:
	Il costruttore di Copia e l'operatore di assegnazione NON SONO SICURI!
	Questo perché per eseguire la copia del font specificato il sistema proverà il ricaricamento
	con i parametri dell'operando dalla quale eseguire la copia. Tale risorsa, quindi, potrebbe
	non essere più disponibile. Tenere a mente questa cosa!*/
	Font(const Font& oth):prtFont(NULL),load_memory_rm(NULL),size_memory_rm(0),size_rm(oth.size_rm),style_rm(oth.style_rm),h_font(0){
		Font::Copy_Font(oth,*this);
	}
	Font& operator=(const Font& oth){
		this->h_font=0;
		Font::Copy_Font(oth,*this);
		return *this;
	}
	~Font(void){
		this->UnLoad();
	}

public:		//CARICAMENTO FONT
	const bool Load(const std::string& packname, const std::string filename, const int size_font=-1, const XGRAPH_FONT_STYLE style =XGRAPH_FONT_STYLE_NOTSET){
		this->UnLoad();
		if(filename.size()==0){
			this->_logError+="Font: è stato tentato il caricamento di un file a valori NULLI!\n";
			return false;
		}
		if(size_font!=-1){
			this->size_rm=size_font;
		}
		if(this->size_rm<=0){
			this->size_rm=12;
		}

		if(style!=XGRAPH_FONT_STYLE_NOTSET){
			this->style_rm=style;
		}
		if(this->style_rm==XGRAPH_FONT_STYLE_NOTSET){
			this->style_rm=XGRAPH_FONT_STYLE_NORMAL;
		}

		std::string load_result;
		if(packname.size()==0){
			load_result=filename;
		}else{
			load_result=packname+'/'+filename;
		}

		this->prtFont=TTF_OpenFont(load_result.c_str(),this->size_rm);
		if(this->prtFont==NULL){
			this->_logError+="Font: Impossibile caricare il font richiesto.\n";
			this->_logError+=TTF_GetError();
			this->_logError+='\n';
			return false;
		}

		this->packname_rm=packname;
		this->filename_rm=filename;
		this->load_memory_rm=NULL;
		this->size_memory_rm=0;
		this->h_font=TTF_FontHeight(this->prtFont);
		this->Set_FontStyle(style);
		return true;

	}
	const bool Load_From_Memory(void* memory, const int size_memory, const int size_font=-1, const XGRAPH_FONT_STYLE style =XGRAPH_FONT_STYLE_NORMAL){
		this->UnLoad();
		if(memory==NULL || size_memory==0){
			this->_logError+="Font: è stato tentato il caricamento di un file a valori NULLI!\n";
			return false;
		}

		if(size_font!=-1){
			this->size_rm=size_font;
		}
		if(this->size_rm<=0){
			this->size_rm=12;
		}

		if(style!=XGRAPH_FONT_STYLE_NOTSET){
			this->style_rm=style;
		}
		if(this->style_rm==XGRAPH_FONT_STYLE_NOTSET){
			this->style_rm=XGRAPH_FONT_STYLE_NORMAL;
		}

		SDL_RWops* pMem=SDL_RWFromMem(memory, size_memory);
		if(pMem==NULL){
			this->_logError+="Area di memoria corrotta. Impossibile effettuare un'operazione di caricamento per la texture indicata.\n";
			return false;
		}
		this->prtFont=TTF_OpenFontRW(pMem, 1, this->size_rm);
		if(this->prtFont==NULL){
			this->_logError+="Font: Impossibile caricare il font richiesto.\n";
			this->_logError+=TTF_GetError();
			this->_logError+='\n';
			return false;
		}
		this->filename_rm.clear();
		this->packname_rm.clear();
		this->load_memory_rm=memory;
		this->size_memory_rm=size_memory;
		this->h_font=TTF_FontHeight(this->prtFont);
		this->Set_FontStyle(style);
		return true;
	}

	void UnLoad(void){
		if(this->prtFont){
			TTF_CloseFont(this->prtFont);
			this->prtFont=NULL;
		}
	}

	const bool Is_Load(void) const{
		if(this->prtFont) return true;
		return false;
	}

public:		//METODI SET&GET
	const bool Set_FontStyle(const XGRAPH_FONT_STYLE setter){
		if(this->prtFont){
			switch(setter){
			case XGRAPH_FONT_STYLE_NOTSET:
				break;
			case XGRAPH_FONT_STYLE_NORMAL:
				TTF_SetFontStyle(this->prtFont, TTF_STYLE_NORMAL);
				break;
			case XGRAPH_FONT_STYLE_BOLD:
				TTF_SetFontStyle(this->prtFont, TTF_STYLE_BOLD);
				break;
			default:
				this->_logError+="Font: Impossibile eseguire il comando specificato per lo stile del font!";
				return false;
				break;
			}
		}
		return true;
	}

	inline const int Get_H_Font(void) const{
		return this->h_font;
	}











public:		//OPERATORI CAST&OPERAZIONALI
	operator TTF_Font*(void){
		return this->prtFont;
	}

	operator const TTF_Font*(void) const{
		return this->prtFont;
	}



private:	//DATA
	TTF_Font* prtFont;
	void* load_memory_rm;
	int size_memory_rm;
	std::string packname_rm;
	std::string filename_rm;
	int size_rm;
	XGRAPH_FONT_STYLE style_rm;
	std::string _logError;
	int h_font;

private:	//FUNZIONI DI SUPPORTO INTERNE
	inline static void Copy_Font(const Font& f1, Font& f2){
		if(f1.size_memory_rm>0){
			f2.Load_From_Memory(f1.load_memory_rm,f1.size_memory_rm,f1.size_rm,f1.style_rm);
			//TODO: valutare i rischi di caricare il font da un'area di memoria che potrebbe non esiste più!
		}else{
			f2.Load(f1.packname_rm,f1.filename_rm,f1.size_rm,f1.style_rm);
		}
	}
};

#endif