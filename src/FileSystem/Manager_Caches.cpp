#include <XGraph/FileSystem/Manager_Caches.h>
#include <vector>


Manager_Caches* Manager_Caches::m_pInstance=NULL;
Manager_Caches::Manager_Caches(void){
	this->Set_Default_MaxMemoryUsed();
}
Manager_Caches::Manager_Caches(const Manager_Caches& oth){
	this->Set_Default_MaxMemoryUsed();
}
Manager_Caches& Manager_Caches::operator=(const Manager_Caches& oth){
	this->Set_Default_MaxMemoryUsed();
	return *this;
}

const bool Manager_Caches::CheckPage(const std::string& pathname, const std::string& filename, Page& mem_out){
	Cache* cur=this->Find_Cache(pathname,filename);
	this->AbbassaFrequenza_allCaches();
	if(cur==NULL){
		return false;
	}
	cur->MakePage_fromThisCache(mem_out);
	return true;
}

void Manager_Caches::AddCache(const std::string& pathname, const std::string& filename, const Page& mem_in){
	if(this->Find_Cache(pathname,filename)==NULL){
		this->PulisciCaches();
		this->_list_caches.insert(std::pair<id_cache,Cache*>(id_cache(pathname,filename),new Cache(mem_in)));
	}
}

short Manager_Caches::id_cache::_operator_less(const std::string& str1, const std::string& str2){
	size_t len1=str1.size();
	size_t len2=str2.size();
	unsigned int len_minor;
	if(len1 > len2) len_minor=len2;
	if(len1 < len2) len_minor=len1;
	if(len1 == len2)len_minor=len1;

	short result;
	for(unsigned int i=0; i<len_minor; i++){
		result=Manager_Caches::id_cache::_operator_less(str1[i],str2[i]);
		if(result==1){
			return 1;
		}
		if(result==-1){
			return -1;
		}
	}

	if(len1==len2) return 0;
	if(str1.size() < str2.size()){
		return -1;
	}
	return 1;
}

const long Manager_Caches::Get_MemoryUsed(void) {
	std::map<id_cache,Cache*>::iterator it;
	long rts=0;
	for(it=this->_list_caches.begin(); it!=this->_list_caches.end(); it++){
		rts+=(*it).second->Size_inbytes();
	}
	return rts;
}

void Manager_Caches::PulisciCaches(void){
	if(this->Get_MemoryUsed() > this->max_bytes_memory){
		unsigned int size=(unsigned int)(this->_list_caches.size()/2);
		if(size==0) size=1;
		std::map<id_cache,Cache*>::iterator it;
		for(unsigned int i=0; i<size; i++){
			if(this->Get_LastFrequecy(it)){
				delete (*it).second;
				(*it).second=NULL;
				this->_list_caches.erase(it);
			}
		}
	}
}

void Manager_Caches::AbbassaFrequenza_allCaches(void){
	register std::map<id_cache,Cache*>::iterator it;
	for(it=this->_list_caches.begin(); it!=this->_list_caches.end(); it++){
		(*it).second->Reduct_Frequency();
	}
}

bool Manager_Caches::Get_LastFrequecy(std::map<id_cache,Cache*>::iterator& it_mod){
	register std::map<id_cache,Cache*>::iterator it;
	it_mod=this->_list_caches.end();
	for(it=this->_list_caches.begin(); it!=this->_list_caches.end(); it++){
		if(it_mod==this->_list_caches.end()){
			it_mod=it;
		}else{
			if((*it).second->Crit_Used() < (*it_mod).second->Crit_Used()){
				it_mod=it;
			}
		}
	}
	if(it_mod==this->_list_caches.end()){
		return false;
	}
	return true;
}