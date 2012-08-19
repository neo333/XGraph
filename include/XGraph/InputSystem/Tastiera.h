#ifndef __TASTIERA__IS
#define __TASTIERA__IS

#include <SDL/SDL.h>
#include <cassert>
#include <string>
#include <vector>

class Gestore_Input;

class Tastiera{
public:		//INTERFACCIA
	inline static Tastiera& Get_Instance(void){
		if(Tastiera::m_pInstance==NULL){
			Tastiera::m_pInstance=new Tastiera();
			assert(Tastiera::m_pInstance);
		}
		return *Tastiera::m_pInstance;
	}
	


	/*Svuota il buffer della tastiera*/
	void Flush_Buffer(void){
		this->buffer_key.clear();
	}



	/*POP del buffer!*/
	const bool Get_charBuffer(Uint16& rts){
		/*Prende (ritorna e cancella: pop) l'ultimo carattere nel buffer della tastiera.
	
	PARAMETRI:
		> Uint16& (OUTPUT)		->		Carattere -unicode- prossimo all'uscita dal buffer.
	
	RITORNO:
		> const bool			->		Ritorna 'true' se è stato effettivamente preso un carattere
										dal buffer (e copiato nel parametro d'uscita della funzione).
										Altrimenti 'false'.*/
		if(this->buffer_key.size()==0) return false;
		rts=this->buffer_key.front();
		this->buffer_key.erase(this->buffer_key.begin());
		return true;
	}

	const Uint8* Get_snapState_Key(void) const{
		/*Ritorna un istantanea di tutto lo stato della tastiera*/
		return this->key_snap;
	}




private:		//SINGLETON REALIZATION
	friend class Gestore_Input;
	Tastiera(void);
	Tastiera(const Tastiera&);
	Tastiera& operator=(const Tastiera&);
	static Tastiera* m_pInstance;
	static const unsigned int DIM_BUFFER;

private:	//DATA
	std::vector<Uint16> buffer_key;
	void Put_into_Buffer(const Uint16& adder){
		/*Aggiunge un carattere UNICODE al buffer della tastiera*/
		if(this->buffer_key.size() >= Tastiera::DIM_BUFFER){
			this->buffer_key.erase(this->buffer_key.begin());
		}
		this->buffer_key.push_back(adder);
	}

	Uint8* key_snap;
	void UpDate_Array_Key(void){
		this->key_snap=SDL_GetKeyState(NULL);
	}
};

#define ctrl_Tastiera Tastiera::Get_Instance()

#endif