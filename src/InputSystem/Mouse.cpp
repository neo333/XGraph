#include <XGraph/InputSystem/Mouse.h>

Mouse::Mouse(void):_bleft(false),_bright(false),_bmiddle(false){

}
Mouse::Mouse(const Mouse& oth){

}
Mouse& Mouse::operator=(const Mouse& oth){
	return *this;
}
Mouse* Mouse::m_pInstance=NULL;