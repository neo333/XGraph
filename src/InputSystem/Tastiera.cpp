#include <XGraph/InputSystem/Tastiera.h>

Tastiera* Tastiera::m_pInstance=NULL;
const unsigned int Tastiera::DIM_BUFFER=100;
Tastiera::Tastiera(void){
}
Tastiera::Tastiera(const Tastiera& oth){

}
Tastiera& Tastiera::operator=(const Tastiera& oth){
	return *this;
}
