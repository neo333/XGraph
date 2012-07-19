#ifndef __CACHE__FS
#define __CACHE__FS

#include <XGraph/FileSystem/Page.h>
#include <string>
#include <SDL/SDL.h>
#include <cmath>
#include <XGraph/_begin.h>

class XGRAPH_DLLAPI Cache{
private:
	static const Uint32 decadiment_frequency;
	const Page _internal_page;
	double frequency;
	Uint32 time_start;

	Cache(const Cache& oth):frequency(0){

	}
	Cache& operator=(const Cache& oth){
		this->frequency=oth.frequency;
		return *this;
	}
public:
	/*Costruisce la cache facendo una COPIA della pagina di memoria passatogli come parametro*/
	Cache(const Page& cp_page): _internal_page(cp_page),frequency(0),time_start(SDL_GetTicks()){

	}

	/*Crea una pagina di memoria facendo una copia di questa cache*/
	void MakePage_fromThisCache(Page& mem_out){
		this->frequency+=exp((double)((SDL_GetTicks()-this->time_start)*-1)/(3*Cache::decadiment_frequency));
		if(this->frequency>1) this->frequency=1;
		this->time_start=SDL_GetTicks();
		mem_out=this->_internal_page;
	}

	/*Ritorna in bytes la dimensione della caches*/
	const long& Size_inbytes(void) const{
		return this->_internal_page.mem_size;
	}

	/*Riduce la frequenza delle volte chiamate*/
	void Reduct_Frequency(void){
		this->frequency-=0.1;
		if(this->frequency<0) this->frequency=0;
	}

	/*Ritorna un valore indicativo che intende QUANTO la cache viene utilizzata.
	Questo valore è compreso tra 0 e 1 (reale)*/
	const double& Crit_Used(void) const{
		return this->frequency;
	}
};

#endif