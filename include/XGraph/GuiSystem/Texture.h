#ifndef __TEXTURE__GUI
#define __TEXTURE__GUI

#include <SDL/SDL_image.h>
#include <string>
#include <XGraph/FileSystem/HardDisk.h>
#include <XGraph/GuiSystem/Color.h>
#include <XGraph/GuiSystem/Rect.h>

class Texture{
public:		//COSTRUTTORI E CARICAMENTO
	Texture(SDL_Surface* pinit=NULL):mp_surface(pinit){

	}
	Texture(const Texture& oth):mp_surface(internal_Copy_SDLSurface(oth.mp_surface)){
		
	}
	
	
	
	/*Crea una Texture vuota (che è, però, caricata!) (un rettangolo nero per intenderci)
	Questo metodo di costruzione può risultare utile quando si deve
	creare una texture componendola di varie parti di altre textures.
	Una volta creata la texture delle dimensioni richieste è possibile "sovrapporre" pezzi di texture precedentemente caricate
	attraverso la funzione membro di questa classe apposita!*/
	Texture(const int n_width, const int n_height);
	
	
	
	Texture& operator=(const Texture& oth){
		this->Delete();
		this->mp_surface=this->internal_Copy_SDLSurface(oth.mp_surface);
		return *this;
	}
	Texture& operator=(SDL_Surface* oth){
		this->Delete();
		this->mp_surface=oth;
		return *this;
	}
	~Texture(void){
		this->Delete();
	}
	void Delete(void){
		if(this->mp_surface){
			SDL_FreeSurface(this->mp_surface);
			this->mp_surface=NULL;
		}
	}

	/*Carica la texture da un file immagine fisico.
	PARAMETRI:
		> const std::string& (pathname)		=		Percorso del file
		> const std::string& (filename)		=		Nome (completo di estensione) del file
		> const bool						=		Se 'true' indica di caricare l'immagine col colore trasparente definito
		
	RITORNO:
		La funzione 'true' se la texture viene caricata correttamente, altrimenti false.
		
	NOTE:
		Questa funzione può essere chiamata solamente dopo aver avviato la finestra grafica dell'applicazione
		altrimenti l'operazione di ottimizzazione bloccherà il processo*/
	const bool Load(const std::string& pathname, const std::string& filename, const bool src_trasparent=true){
		this->Delete();
		Page memory_add;
		if(HardDisk::Get_Instance().LoadFile_fromHardDisk(pathname,filename,memory_add)==false){
			this->last_error="Impossibile caricare la texture richiesta\n";
			this->last_error+=HardDisk::Get_Instance().Get_LastError();
		}else{
			if(this->_load_from_memory(memory_add.Get_Memory(),memory_add.Get_Size(),src_trasparent)==false){
				
			}else{
				memory_add.FreeMemory();
				return true;
			}
		}
		memory_add.FreeMemory();
		return false;
	}
	
	
	/*Carica la texture da una risorsa immagine caricata precedentemente in memoria
	NOTE:
		Questa funzione effettua una COPIA dell'aria di memoria passata come parametro, quindi appena dopo il caricamento
		potrà essere liberata a piacimento senza problemi
		
		L'immagine verrà caricata SENZA (in ogni caso) algoritmo di cifratura!*/
	const bool Load_fromMemory(void* area_memory, const long& size_memory, const bool src_trasparent=true){
		this->Delete();
		return this->_load_from_memory(area_memory,size_memory,src_trasparent);
	}


	const bool Is_Load(void) const{
		if(this->mp_surface){
			return true;
		}
		return false;
	}
	const bool Is_Error(void) const{
		if(this->last_error.size()>0){
			return true;
		}
		return false;
	}
	const std::string& Last_Error(void) const{
		return this->last_error;
	}






public:		//METODI DI GET&SET
	const Sint16 Get_Width(void) const{
		if(this->mp_surface){
			return this->mp_surface->w;
		}
		return 0;
	}
	const Sint16 Get_Height(void) const{
		if(this->mp_surface){
			return this->mp_surface->h;
		}
		return 0;
	}

	SDL_Surface* Get_Surface(void){
		return this->mp_surface;
	}
	
	const bool Set_ColorKey(const Color& setter){
		if(this->mp_surface){
			Uint32 _mod=SDL_MapRGB(this->mp_surface->format,setter.Get_Red(),setter.Get_Green(),setter.Get_Blue());
			if(SDL_SetColorKey(this->mp_surface,SDL_SRCCOLORKEY | SDL_RLEACCEL, _mod)!=0){
				this->last_error=SDL_GetError();
				return false;
			}
		}
		return true;
	}
	const Color Get_ColorKey(void) const{
		if(this->mp_surface){
			Uint32 colorKey=this->mp_surface->format->colorkey;

			Uint8 red = (Uint8)(colorKey >> 16);
			Uint8 green = (Uint8)(colorKey >> 8);
			Uint8 blue = (Uint8)(colorKey);

			return Color(red,green,blue);
		}
		return Color();
	}






public:		//FUNZIONI AGGIUNTIVE
	/*Esegue un blit (copia una texture su di un'altra) di una texture su 'questa'
	Indicare la posizione di questa texture sul quale eseguire la copia della texture sorgente*/
	const bool Paste_Texture(const Texture& source, const Point& xy, const Rect& cut =Rect(Point(0,0),0,0)){
		if(this->Is_Load() && source.Is_Load()){
			SDL_Rect _xy;
			_xy.x=xy.Get_X();
			_xy.y=xy.Get_Y();
			SDL_Rect _cut=cut;
			if(_cut.w==0){
				_cut.w=source.Get_Width();
			}
			if(_cut.h==0){
				_cut.h=source.Get_Height();
			}

			if(SDL_BlitSurface(source.mp_surface, &_cut, this->mp_surface, &_xy)==0){
				return true;
			}
		}
		return false;
	}





public:		//OPERATORI
	operator SDL_Surface*(void){
		return this->mp_surface;
	}

	operator const SDL_Surface*(void) const{
		return this->mp_surface;
	}

	

	






















private:		//FUNZIONI MEMBRO PRIVATE E DATA
	SDL_Surface* mp_surface;
	std::string last_error;

	SDL_Surface* internal_Copy_SDLSurface(SDL_Surface* oth){
		if(oth){
			SDL_Surface* rts;
			rts=SDL_DisplayFormat(oth);
			if(rts==NULL){
				this->last_error=SDL_GetError();
			}
			return rts;
		}
		return NULL;
	}

	/*carica l'SDL_Surface interna dalla memoria
	Ritorna true se l'immagine viene caricata ed ottimizzata correttamente.
	la surface interna della classe deve essere liberata PRIMA di chiamare questa funzione!
	NOTA BENE: La memoria di input può essere deallocata senza problemi sicché la surface verrà caricata in un'area
	di memoria separata!!
	PS: definire trasp_key=true per caricare l'immagine con i pixel trasparenti direttamente dalla sorgente*/
	const bool _load_from_memory(void* memory, const long& size, const bool trasp_key){
		bool ok_status=false;
		SDL_RWops* pMem=SDL_RWFromMem(memory, size);
		if(pMem==NULL){
			this->last_error="Area di memoria corrotta. Impossibile effettuare un'operazione di caricamento per la texture indicata.";
			
		}else{
			SDL_Surface* buf_temp=IMG_Load_RW(pMem, 0);
			SDL_FreeRW(pMem);
			if(buf_temp==NULL){
				this->last_error="Impossibile caricare la risorsa texture richiesta.\n";
				this->last_error+=IMG_GetError();
			}else{
				if(trasp_key==true){
					if(SDL_SetColorKey(buf_temp,SDL_RLEACCEL | SDL_SRCCOLORKEY,buf_temp->format->colorkey)!=0){
						this->last_error="Impossibile ottimizzare la risorsa texture richiesta tramite RLEACCEL.\n";
						this->last_error+=SDL_GetError();
						return false;
					}
				}
				this->mp_surface=SDL_DisplayFormat(buf_temp);
				SDL_FreeSurface(buf_temp);
				buf_temp=NULL;
				if(this->mp_surface==NULL){
					this->last_error="Impossibile ottimizzare la risorsa texture richiesta.\n";
					this->last_error+=SDL_GetError();
					return false;
				}
				return true;
			}
		}
		return false;
	}
};

#endif