#ifndef __HARD_DISK__FS
#define __HARD_DISK__FS

#include <cassert>
#include <string>
#include <cstdio>
#include <XGraph/FileSystem/Page.h>
#include <XGraph/_begin.h>


class XGRAPH_DLLAPI HardDisk{
public:		//INTERFACCIA
	static HardDisk& Get_Instance(void){
		if(HardDisk::m_pInstance==NULL){
			HardDisk::m_pInstance=new HardDisk();
			assert(HardDisk::m_pInstance);
		}
		return *HardDisk::m_pInstance;
	}

	/*Ritorna l'ultimo errore verificatosi in un formato intellegibile*/
	const std::string& Get_LastError(void) const{
		return this->last_error;
	}


	/*Ritorna una pagina di memoria contentente un file che verrà caricato dall'hard disk.
	PARAMETRI:
		> const std::string&	->		Percorso (path; cartella) contenente il file FISICO da caricare
		> const std::string&	->		Nome del file (completo di estensione) FISICO da caricare
		> Page&					->		Output dell'operazione. La pagina di memoria dove verrà caricato il file FISICO
	
	RITORNO:
		true					->		L'operazione è andata a buon fine. Page sarà il FILE VIRTUALE
		false					->		L'operazione è fallita. Consulare 'Get_LastError' per maggiori dettagli
		
	VINCOLI:
		> La 'Pagina' (Page; parametro di uscita) deve essere vuoto!
		> Se ritorna 'false' PAGE non sarà caricata e sarà vuota!
		
	NOTE AGGIUNTIVE:
		La seguente funzione utilizza i componenti 'Manager_Caches' & 'De_Encoder' del sistema.
		L'operazione, infatti, prevede l'accesso alle caches del sistema e la decodifica del file fisico stesso
		attraverso la chiave di cifratura settabile dal componente 'De_Encoder' stesso.*/
	const bool LoadFile_fromHardDisk(const std::string&, const std::string&, Page&);




private:		//FUNZIONI MEMBRO PRIVATE
	HardDisk(void);
	HardDisk(const HardDisk&);
	HardDisk& operator=(const HardDisk&);

	static HardDisk* m_pInstance;
	std::string last_error;

	/*Carica un'area di memoria da file!
	L'area di memoria deve essere deallocata quando non servirà più (utilizzando delete[] area).
	Il file DEVE esistere (fare un controllo prima di chiamare questa funzione)
	ritorna NULL in caso di errore, ma non scrive niente sulla stringa dell'ultimo errore! (grazie, è static)*/
	static char* _load_tofile(long&, const std::string&);

	//funzioni di supporto
	static const bool File_Exist(const std::string& pathname){
		FILE* pFile;
#ifdef MVISUAL_STUDIO_COMPILER
		fopen_s(&pFile,pathname.c_str(),"rb");
#else
		pFile=fopen(pathname.c_str(),"rb");
#endif
		if(pFile==NULL) return false;
		fclose(pFile);
		pFile=NULL;
		return true;
	}
};

#endif