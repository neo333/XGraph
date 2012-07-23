#include <XGraph/FileSystem/HardDisk.h>
#include <XGraph/FileSystem/De_Encoder.h>
#include <XGraph/FileSystem/Manager_Caches.h>

HardDisk* HardDisk::m_pInstance=NULL;
HardDisk::HardDisk(void){

}
HardDisk::HardDisk(const HardDisk& oth){

}
HardDisk& HardDisk::operator=(const HardDisk& oth){
	return *this;
}

const bool HardDisk::LoadFile_fromHardDisk(const std::string& cartella, const std::string& nomefile, Page& page_out){
	if(page_out.mem_pointer!=NULL){
		this->last_error="HD: E' stata provata a caricare un'area di memoria già utilizzata";
	}else{
		//verifica che il file sia già presente nelle caches del sistema
		if(Manager_Caches::Get_Instance().CheckPage(cartella,nomefile,page_out)==true){
			return true;
		}
		//--------------------------------------------------------------
		std::string pathname_complete;
		if(cartella.size()>0){
			pathname_complete=cartella+'/'+nomefile;
		}else{
			pathname_complete=nomefile;
		}
		if(HardDisk::File_Exist(pathname_complete)==false){
			this->last_error="HD: Impossibile trovare la risorsa richiesta!\n"
				" Risorsa: ["+cartella+"/"+nomefile+"]";
		}else{
			page_out.mem_pointer=HardDisk::_load_tofile(page_out.mem_size,pathname_complete);
			if(page_out.mem_pointer==NULL){
				this->last_error="HD: Impossibile leggere l'area di memoria richiesta!";
			}else{
				if(De_Encoder::Get_Instance().DecodificaPagina(page_out)==false){
					this->last_error="HD: Impossibile effettuare la decodificazione della risorsa richiesta";
					page_out.FreeMemory();
				}else{
					//inserisco nelle caches del sistema!
					Manager_Caches::Get_Instance().AddCache(cartella,nomefile,page_out);
					//-----------------------
					return true;
				}
			}
		}
	}
	return false;
}

char* HardDisk::_load_tofile(long& out_size, const std::string& pathname){
	out_size=0;
	FILE* pFile;
#ifdef MVISUAL_STUDIO_COMPILER
	fopen_s(&pFile,pathname.c_str(),"rb");
#else
	pFile=fopen(pathname.c_str(),"rb");
#endif
	if(pFile==NULL){
		return NULL;
	}
	fseek(pFile, 0, SEEK_END);
	out_size=ftell(pFile);
	rewind(pFile);
	char* rts=new char[out_size];
	fread((void*)rts,out_size,1,pFile);
	fclose(pFile);
	pFile=NULL;
	return rts;
}

	