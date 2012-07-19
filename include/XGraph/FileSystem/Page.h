#ifndef __PAGE__FS
#define __PAGE__FS

#include <XGraph/_begin.h>

#ifndef NULL
#define NULL 0
#endif

class HardDisk;
class De_Encoder;
class Cache;

class XGRAPH_DLLAPI Page{
private:
	friend class HardDisk;
	friend class De_Encoder;
	friend class Cache;

	char* mem_pointer;
	long mem_size;

	/*Allora una nuova area di memoria, dalla COPIA di un'altra.
	NOTA: l'area di memoria ritornata deve essere DEALLOCATA con delete[] area
	NOTA2: _size è la dimensione dell'area puntata in BYTES*/
	static char* CopyMemoryArea(const char* _area,const long& _size){
		if(_area==NULL || _size==0){
			return NULL;
		}
		char* rts=new char[_size];
		for(register int i=0; i<_size; i++){
			rts[i]=_area[i];
		}
		return rts;
	}

	Page(const Page& oth):mem_pointer(Page::CopyMemoryArea(oth.mem_pointer,oth.mem_size)),mem_size(oth.mem_size){

	}
	Page& operator=(const Page& oth){
		this->FreeMemory();
		this->mem_pointer=Page::CopyMemoryArea(oth.mem_pointer,oth.mem_size);
		this->mem_size=oth.mem_size;
		return *this;
	}
public:
	Page(void):mem_pointer(NULL),mem_size(0){

	}	
	~Page(void){
		this->FreeMemory();
	}
	void FreeMemory(void){
		if(this->mem_pointer){
			delete[] this->mem_pointer;
			this->mem_pointer=NULL;
			this->mem_size=0;
		}
	}
	const long& Get_Size(void) const{
		return this->mem_size;
	}
	void* Get_Memory(void){
		return (void*)(this->mem_pointer);
	}
};

#endif