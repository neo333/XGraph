#include <XGraph/InputSystem/Gestore_Input.h>

Gestore_Input::Gestore_Input(void):force_quit_app(false){

}
Gestore_Input::Gestore_Input(const Gestore_Input& oth){

}
Gestore_Input& Gestore_Input::operator=(const Gestore_Input& oth){
	return *this;
}
Gestore_Input* Gestore_Input::m_pInstance=NULL;