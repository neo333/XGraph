#ifndef __RECT__GUI
#define __RECT__GUI

#include <XGraph/GuiSystem/Point.h>
#include <XGraph/GuiSystem/SDL_collide.h>
#include <XGraph/_begin.h>

class XGRAPH_DLLAPI Rect{

public:		//COSTRUTTORI
	Rect(const Point& start_coord=(0,0), const Sint16& w_param=0, const Sint16& h_param=0):_xy_(start_coord), w(w_param), h(h_param){

	}



public:		//METODI SET&GET
	void Set_Position(const Point& xy_position){
		this->_xy_=xy_position;
	}
	void Set_W(const Sint16& w_param){
		this->w=w_param;
	}
	void Set_H(const Sint16& h_param){
		this->h=h_param;
	}
	const Point& Get_Position(void) const{
		return this->_xy_;
	}
	const Sint16& Get_W(void) const{
		return this->w;
	}
	const Sint16& Get_H(void) const{
		return this->h;
	}




public:		//FUNZIONI AGGIUNTIVE STATICHE
	/*Verifica se due Rect sono sovrapposte.
	Ritorna 'true' se la condizione è verificata, altrimenti false*/
	static const bool Rect_Collide(const Rect& r1, const Rect& r2){
		if(SDL_CollideBoundingBox(r1, r2)){
			return true;
		}
		return false;
	}


public:		//CASTING
	operator SDL_Rect(void) const{
		SDL_Rect rts;
		rts.x=this->_xy_.Get_X();
		rts.y=this->_xy_.Get_Y();
		rts.w=this->w;
		rts.h=this->h;
		return rts;
	}



public:			//OPERATORI
	operator const bool(void) const{
		if(this->w | this->h){
			return true;
		}
		return false;
	}








private:		//PRIVATE: DATA
	Point _xy_;
	Sint16 w;
	Sint16 h;
};

#endif