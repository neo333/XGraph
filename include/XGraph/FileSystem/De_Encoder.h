#ifndef __DE_ENCORDE__FS
#define __DE_ENCORDE__FS

#include <cassert>
#include <XGraph/FileSystem/Page.h>
#include <XGraph/_begin.h>

class XGRAPH_DLLAPI De_Encoder{
private:
	De_Encoder(void);
	De_Encoder(const De_Encoder&);
	De_Encoder& operator=(const De_Encoder&);

	int key_cryp;

	static De_Encoder* m_pInstance;
	void Set_Default_Key(void);


public:		//INTERFACCIA
	static De_Encoder& Get_Instance(void){
		if(De_Encoder::m_pInstance==NULL){
			De_Encoder::m_pInstance=new De_Encoder();
			assert(De_Encoder::m_pInstance);
		}
		return *De_Encoder::m_pInstance;
	}


	/*Decodifica la pagina riportata secondo la chiave di cifratura settata.
	PARAMETRI:
		> Page& (INPUT_OUTPUT)		->		La pagina di memoria da decodificare.
	
	RITORNO:
		> const bool				->		Ritorna 'true' se l'operazione va a buon fine, altrimenti 'false'.*/
	const bool DecodificaPagina(Page&);
	
	
	/*TODO: funzione non implementata. Ritorna false.*/
	const bool CodificaPagina(Page&);


	/*Setta la chiave di cifratura del De_Encoder (se questa funzione non viene chiamata la chiave di cifratura
	di default sarà pari a 0).
	Ricorda: una pagina cifrata con una determinata chiave di cifratura potrà essere decifrata
	solo attraverso la stessa chiave di cifratura.*/
	void Set_Key(const int& setter){
		this->key_cryp=setter;
	}
};

#endif