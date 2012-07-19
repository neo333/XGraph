#include <XGraph/FileSystem/De_Encoder.h>

De_Encoder* De_Encoder::m_pInstance=NULL;
De_Encoder::De_Encoder(void){
	this->Set_Default_Key();
}
De_Encoder::De_Encoder(const De_Encoder& oth){
	this->Set_Default_Key();
}
De_Encoder& De_Encoder::operator=(const De_Encoder& oth){
	this->Set_Default_Key();
	return *this;
}
void De_Encoder::Set_Default_Key(void){
	this->key_cryp=0;
}

const bool De_Encoder::DecodificaPagina(Page& page_mem){
	if(page_mem.mem_pointer==NULL){
		return false;
	}
	for(register int i=0; i<page_mem.mem_size; i++){
		page_mem.mem_pointer[i]=page_mem.mem_pointer[i]-this->key_cryp;
	}
	return true;
}

const bool De_Encoder::CodificaPagina(Page& page_mem){
	return false;
}