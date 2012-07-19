#ifndef __MANAGER_CACHES__FS
#define __MANAGER_CACHES__FS

#include <XGraph/FileSystem/Cache.h>
#include <cassert>
#include <map>
#include <XGraph/_begin.h>

class XGRAPH_DLLAPI Manager_Caches{
public:		//INTERFACCIA
	static Manager_Caches& Get_Instance(void){
		if(Manager_Caches::m_pInstance==NULL){
			Manager_Caches::m_pInstance=new Manager_Caches();
			assert(Manager_Caches::m_pInstance);
		}
		return *Manager_Caches::m_pInstance;
	}



	/*Controlla se è già presente una page con i valori definiti nei paramtri.
	In caso positivo assegna a Page passata come parametro una nuova area come copia.
	PARAMETRI:
		>	(INPUT) std::string&		->		pattern(cartella) dove è presente il file fisico da caricare
		>	(INPUT) std::string&		->		nome del file fisico da caricare
		>	(OUTPUT) Page&				->		L'area di memoria dove verrà fatta la copia eventuale del file virtuale
	RITORNO:
		> const bool					->		Ritorna true se una caches già caricata è stata trovata nel sistema.
												In caso di true, quindi, il file sarà caricato su Page& passato nel parametro
												Ritorna false in caso non sia presente nessuna cache.
	VINCOLI:
		> Page& DEVE ESSERE un'area di memoria LIBERA!
	*/
	const bool CheckPage(const std::string&, const std::string&, Page&);
	
	



	/*Aggiunge una cache al sistema.
	PARAMETRI:
		>	(INPUT) std::string&		->		pattern(cartella) dove è presente il file fisico da caricare
		>	(INPUT) std::string&		->		nome del file fisico da caricare
		>	(INPUT) const Page&			->		Pagina della memoria che verrà COPIATA come cache!
	VINCOLI:
		Assicurarsi che la Page che verrà copiata (quella del parametro) sia già decodificata e caricata per bene!
	*/
	void AddCache(const std::string&, const std::string&, const Page&);





	/*Ritorna in BYTES la memoria utilizzata dalle chaches*/
	const long Get_MemoryUsed(void);





	/*Setta la quantità di memoria massima (in bytes) che verrà usata per archiviare i bites.
	Indicare un valore negativo per selezionare il parametro di default (100 MB)*/
	void Set_MaxMemoryUsed(const long& _size){
		this->max_bytes_memory=_size;
		if(this->max_bytes_memory<0) this->Set_Default_MaxMemoryUsed();
	}








private:		//FUNZIONI MEMBRO PRIVATE
	struct id_cache{
		const std::string pack_name;
		const std::string file_name;

		id_cache(const std::string& pack_loc, const std::string& file_loc):pack_name(pack_loc),file_name(file_loc){
		}
		bool operator<(const id_cache& oth) const{
			if(Manager_Caches::id_cache::_operator_less(this->pack_name+this->file_name,oth.pack_name+oth.file_name)==-1){
				return true;
			}
			return false;
		}

		static char _convert_intoUPPERCHAR(const char& c){
			if((int)(c) >= 97 && (int)(c) <= 122){
				return c-32;
			}
			return c;
		}

		/*Ritorna la lettera più piccolo:
		0 = uguali
		-1 = più piccolo il parametro di sinistra
		1 = più piccolo il parametro di destra*/
		static short _operator_less(const char& c1, const char& c2){
			int cod1=(int)(Manager_Caches::id_cache::_convert_intoUPPERCHAR(c1));
			int cod2=(int)(Manager_Caches::id_cache::_convert_intoUPPERCHAR(c2));
			if(cod1<cod2) return -1;
			if(cod1>cod2) return 1;
			return 0;
		}

		static short _operator_less(const std::string&, const std::string&);
	};

	Manager_Caches(void);
	Manager_Caches(const Manager_Caches&);
	Manager_Caches& operator=(const Manager_Caches&);
	static Manager_Caches* m_pInstance;

	std::map<id_cache,Cache*> _list_caches;
	Cache* Find_Cache(const std::string& pathname, const std::string& filename){
		std::map<id_cache,Cache*>::iterator it;
		it=this->_list_caches.find(id_cache(pathname,filename));
		if(it==this->_list_caches.end()){
			return NULL;
		}
		return (*it).second;
	}

	long max_bytes_memory;
	void Set_Default_MaxMemoryUsed(void){
		this->max_bytes_memory=104857600;
	}

	/*Abbassa la priorità di frequenza (la % di utilizzo) di ogni caches*/
	void AbbassaFrequenza_allCaches(void);

	/*Ritorna l'iteratore che contiene la cache con meno % di frequenza.
	Ritorna true se viene trovato almeno 1 elemento*/
	bool Get_LastFrequecy(std::map<id_cache,Cache*>::iterator&);

	/*Se la memoria usata per la conservazione delle caches è troppo elevata quelle con
	meno % di utilizzo vengono cancellate*/
	void PulisciCaches(void);
};

#endif