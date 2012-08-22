#ifndef __IMAGE__GUI
#define __IMAGE__GUI


#include <cmath>
#include <XGraph/GuiSystem/OutVideo.h>
#include <XGraph/GuiSystem/Rect.h>
#include <XGraph/GuiSystem/resize++.h>

class Image{

public:			//COSTRUTTORI
	Image(const Point& pos_init=(0,0)):pos(pos_init),_alpha(SDL_ALPHA_OPAQUE),area_vis(Rect(Point(0,0),Screen.Get_W_Screen(),Screen.Get_H_Screen())){

	}
	Image(const Image& oth):_intSurface(oth._intSurface),area_cut(oth.area_cut),pos(oth.pos),_alpha(oth._alpha),area_vis(oth.area_vis){
		this->Set_Alpha(this->_alpha);
	}
	Image& operator=(const Image& oth){
		this->_intSurface=oth._intSurface;
		this->area_cut=oth.area_cut;
		this->area_vis=oth.area_vis;
		this->pos=oth.pos;
		this->_alpha=oth._alpha;
		this->Set_Alpha(this->_alpha);
		return *this;
	}
	Image& operator=(const Texture& oth){
		this->_intSurface=oth;
		this->Set_Alpha(this->_alpha);
		this->SetCutArea();
		return *this;
	}
	Image(const Texture& _load, const Point& pos_init=(0,0)):_intSurface(_load),pos(pos_init),_alpha(SDL_ALPHA_OPAQUE),area_vis(Rect(Point(0,0),Screen.Get_W_Screen(),Screen.Get_H_Screen())){
		this->SetCutArea();
	}




public:		//METODI SET/GET
	/*Imposta il 'rettangolo di taglio' della texture. Praticamente l'immagine disegnata a video
	sarà l'area espressa nel parametro della texture totale caricata.
	Per valori di larghezza o altezza nulli verranno considerati quelli totali della texture*/
	inline void SetCutArea(const Rect& setter =Rect()){
		this->area_cut=setter;
		if(this->area_cut.Get_W()==0){
			this->area_cut.Set_W(this->_intSurface.Get_Width());
		}else{
			if(this->area_cut.Get_W() + this->area_cut.Get_Position().Get_X() > this->_intSurface.Get_Width()){
				this->area_cut.Set_W(this->_intSurface.Get_Width());
			}
		}
		if(this->area_cut.Get_H()==0){
			this->area_cut.Set_H(this->_intSurface.Get_Height());
		}else{
			if(this->area_cut.Get_H() + this->area_cut.Get_Position().Get_Y() > this->_intSurface.Get_Height()){
				this->area_cut.Set_H(this->_intSurface.Get_Height());
			}
		}
	}

	/*Imposta l'area dello schermo in cui avverrà il disegno dell'immagine in questione
	Le parti di immagine che si troveranno oltre l'area delimitata non verranno disegnate*/
	inline void SetDrawnableArea(const Rect& setter){
		this->area_vis=setter;
	}	
	inline const Rect& GetDrawnableArea(void) const{
		return this->area_vis;
	}
	
	inline void Set_Position(const Point& pp_point){
		this->pos=pp_point;
	}
	const Sint16 Get_Widht(void) const{
		return (this->area_cut.Get_W() - this->area_cut.Get_Position().Get_X());
	}
	const Sint16 Get_Height(void) const{
		return (this->area_cut.Get_H() - this->area_cut.Get_Position().Get_Y());
	}
	const std::string& Get_LastError(void) const{
		return this->last_error;
	}
	inline const Point& Get_Position(void) const{
		return this->pos;
	}

	/*Setta la trasparenza. 255=OPACO, 0=TRASPARENTE*/
	const bool Set_Alpha(const Uint8 setter){
		if(this->_intSurface.Is_Load() && this->_alpha!=setter){
			if(SDL_SetAlpha(this->_intSurface, SDL_SRCALPHA | SDL_RLEACCEL, setter)!=0){
				this->last_error="Impossibile eseguire la funzione di trasparenza per l'immagine!\n";
				this->last_error+=SDL_GetError();
				return false;
			}else{
				this->_alpha=setter;
			}
		}
		return true;
	}
	const Uint8 Get_Alpha(void) const{
		return this->_alpha;
	}

	/*Ridimensiona un'immagine. L'area di CUT (taglio) verrà resettata!
	NOTA BENE: attualmente (versione corrente) l'algoritmo di ridimensionamento
	pare non tener conto dei pixel 'trasparenti' (colorkey)*/
	const bool ResizeImage(const int& wset, const int& hset){
		if(this->_intSurface.Is_Load()){
			Texture temp=SDL_Resize(this->_intSurface, wset, hset,false);
			if(temp==false){
				this->last_error="Impossibile eseguire il ridimensionamento dell'immagine richiesta";
				return false;
			}
			this->_intSurface=temp;
		}
		this->SetCutArea(Rect(Point(0,0),wset,hset));
		return true;
	}

	/*Setta il colore trasparente*/
	const bool Set_ColorKey(const Color& setter){
		return this->_intSurface.Set_ColorKey(setter);
	}




public:		//DISEGNO
	const bool Drawn(void){
		if(this->_intSurface.Is_Load()){
			SDL_Rect position, area_draw;
			SDL_Rect position_mem;
			int result=0;

			position.x=this->pos.Get_X();
			position.y=this->pos.Get_Y();
			area_draw=this->area_cut;
			position_mem.x=position.x;
			position_mem.y=position.y;


			//calcolo area di disegno
			Rect area_image(Point(position.x,position.y),area_draw.w,area_draw.h);
			if(Rect::Rect_Collide(area_image,this->area_vis)==false){
				return true;
			}
			if(position.x < this->area_vis.Get_Position().Get_X()){
				area_draw.x+= this->area_vis.Get_Position().Get_X() - position.x;
				position.x=this->area_vis.Get_Position().Get_X();
				area_draw.w-=this->area_vis.Get_Position().Get_X() - position_mem.x;
			}
			if(position.y < this->area_vis.Get_Position().Get_Y()){
				area_draw.y+= this->area_vis.Get_Position().Get_Y() - position.y;
				position.y=this->area_vis.Get_Position().Get_Y();
				area_draw.h-=this->area_vis.Get_Position().Get_Y() - position_mem.y;
			}
			if(area_draw.w + position.x > this->area_vis.Get_W() + this->area_vis.Get_Position().Get_X()){
				area_draw.w=this->area_vis.Get_W();
				if(position.x > this->area_vis.Get_Position().Get_X()){
					if(area_draw.w - (position.x - this->area_vis.Get_Position().Get_X()) > 0){
						area_draw.w-=position.x - this->area_vis.Get_Position().Get_X();
					}else{
						area_draw.w=0;
					}
				}
			}
			if(area_draw.h + position.y > this->area_vis.Get_H() + this->area_vis.Get_Position().Get_Y()){
				area_draw.h=this->area_vis.Get_H();
				if(position.y > this->area_vis.Get_Position().Get_Y()){
					if(area_draw.h - (position.y - this->area_vis.Get_Position().Get_Y()) > 0){
						area_draw.h-=position.y - this->area_vis.Get_Position().Get_Y();
					}else{
						area_draw.h=0;
					}
				}
			}

			if(area_draw.w!=0 && area_draw.h!=0){
				result=SDL_BlitSurface(this->_intSurface,&area_draw,OutVideo::Get_Instance()._screen,&position);
			}

			if(result!=0){
				this->last_error="Impossibile eseguire il blit dell'immagine!\n";
				this->last_error+=SDL_GetError();
				return false;
			}	
		}
		return true;
	}





public:		//CARICAMENTO


	/*Carica l'immagine richiesta dal disco.
	PARAMETRI:
		> (INPUT) std::string&		->		Percorso (directory) dove si trova il file.
											Ad esempio: "C:/Data"
		> (INPUT) std::string&		->		Nome del file fisico da caricare come immagine.
		> (INPUT) const bool&		->		true = l'immagine viene caricata con i pixel trasparenti di default
											false= l'immagine viene caricata senza pixel trasparenti

	RITORNO:
		> const bool				->		true se l'operazione va a buonfile, altrimenti false.

	NOTE AGGIUNTIVE:
		Le immagini verranno caricate secondo un'algoritmo di cifratura.
		Impostare una chiave di cifratura NULLA (in caso) all'interno del sotto-sistema del FILESYSTEM!
	*/
	const bool Load(const std::string& pack_name, const std::string& file_name, const bool src_keycolor=true){
		this->_alpha=SDL_ALPHA_OPAQUE;
		bool result=_intSurface.Load(pack_name,file_name,src_keycolor);
		if(result==false){
			this->last_error=this->_intSurface.Last_Error();
		}
		this->SetCutArea(this->area_cut);
		return result;
	}




	/*Carica l'immagine richiesta da un'area di memoria.
	PARAMETRI:
		> (INPUT) void*				->		Puntatore all'area di memoria valida. Dove si trova l'immagine
		> (INPUT) const long&		->		Dimensione in bytes dell'area di memoria
		> (INPUT) const bool&		->		true = l'immagine viene caricata con i pixel trasparenti di default
											false= l'immagine viene caricata senza pixel trasparenti

	RITORNO:
		> const bool				->		true se l'operazione va a buonfile, altrimenti false.

	NOTA:
		L'immagine verrà caricata SEMPRE senza algoritmo di cifratura!
	*/
	const bool Load_fromMemory(void* area_memory, const long& size_memory, const bool src_keycolor =true){
		this->_alpha=SDL_ALPHA_OPAQUE;
		bool result=this->_intSurface.Load_fromMemory(area_memory,size_memory,src_keycolor);
		if(result==false){
			this->last_error=this->_intSurface.Last_Error();
			return false;
		}
		this->SetCutArea(this->area_cut);
		return result;
	}





	/*Ritorna true se l'immagine è correttamente caricata*/
	const bool Is_Load(void) const{
		return this->_intSurface.Is_Load();
	}




	/*Dealloca l'immagine liberando le risorse assegnate*/
	void UnLoad(void){
		this->_intSurface.Delete();
	}

	






public:			//FUNZIONI STATICHE AGGIUNTIVE

	/*Ritorna 'true' se il punto del parametro è all'interno dell'area indicata dalla Rect*/
	static const bool Point_inArea(const Point& point, const Rect& area){
		const Sint16& x_p=point.Get_X();
		const Sint16& y_p=point.Get_Y();
		const Sint16& x_r=area.Get_Position().Get_X();
		const Sint16& y_r=area.Get_Position().Get_Y();
		const Sint16& w_r=area.Get_W();
		const Sint16& h_r=area.Get_H();

		if(x_p >= x_r && x_p <= x_r + w_r){
			if(y_p >= y_r && y_p <= y_r + h_r){
				return true;
			}
		}
		return false;
	}

	/*Ritorna un pixel che si trova nelle coordinate specificate nei parametri della funzione*/
	static const bool GetPixel_fromTexture(Texture& tex, const Point& xy, Uint32& pixel_out){
		if(tex.Is_Load()==false) return false;
		if(xy.Get_X()>tex.Get_Width() || xy.Get_Y() > tex.Get_Height() || xy.Get_X()<0 || xy.Get_Y()<0) return false;
		SDL_LockSurface(tex);
		pixel_out=Image::__getpixel(tex,xy.Get_X(),xy.Get_Y());
		SDL_UnlockSurface(tex);
		return true;
	}

	/*Colora un pixel che si trova nelle coordinate specificate nei parametri della funzione
	secondo il valore esadecimale 0xRRGGBBAA*/
	static const bool PutPixel_intoTexture(Texture& tex, const Point& xy, const Uint32 pixel_in){
		if(tex.Is_Load()==false) return false;
		if(xy.Get_X()>tex.Get_Width() || xy.Get_Y() > tex.Get_Height() || xy.Get_X()<0 || xy.Get_Y()<0) return false;
		SDL_LockSurface(tex);
		Image::_putpixel(tex,xy.Get_X(),xy.Get_Y(),pixel_in);
		SDL_UnlockSurface(tex);
	}




	











protected:		//PRIVATE: DATA
	Texture _intSurface;
	Rect area_cut;
	Point pos;
	Rect area_vis;

	std::string last_error;
	Uint8 _alpha;




private:		//FUNZIONI STTICHE DI SUPPORTO (PRIVATE)
	/*getpixel_SDL
	NOTA: la surface deve essere bloccata prima di chiamare questa funzione!*/
	static Uint32 __getpixel(SDL_Surface *surface, const int x, const int y){
		int bpp = surface->format->BytesPerPixel;
		/* Here p is the address to the pixel we want to retrieve */
		Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;
		switch(bpp) {
		case 1:

			return *p;

		case 2:
			return *(Uint16 *)p;

		case 3:
			if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
				return p[0] << 16 | p[1] << 8 | p[2];
			else
				return p[0] | p[1] << 8 | p[2] << 16;

		case 4:
			return *(Uint32 *)p;

		default:
			return 0;       /* shouldn't happen, but avoids warnings */
		}
	}

	/*putpixel_SDL
	NOTA: la surface deve essere bloccata prima di chiamare questa funzione!*/
	static void _putpixel(SDL_Surface *surface, const int x, const int y, const Uint32 pixel){
		int bpp = surface->format->BytesPerPixel;
		/* Here p is the address to the pixel we want to set */
		Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

		switch(bpp) {
		case 1:
			*p = pixel;
			break;

		case 2:
			*(Uint16 *)p = pixel;
			break;

		case 3:
			if(SDL_BYTEORDER == SDL_BIG_ENDIAN) {
				p[0] = (pixel >> 16) & 0xff;
				p[1] = (pixel >> 8) & 0xff;
				p[2] = pixel & 0xff;
			} else {
				p[0] = pixel & 0xff;
				p[1] = (pixel >> 8) & 0xff;
				p[2] = (pixel >> 16) & 0xff;
			}
			break;

		case 4:
			*(Uint32 *)p = pixel;
			break;
		}
	}
};

#endif