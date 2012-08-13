#ifndef __RECT__GUI
#define __RECT__GUI

#include <XGraph/GuiSystem/Point.h>
#include <XGraph/GuiSystem/SDL_collide.h>

class Rect{

public:		//COSTRUTTORI
	Rect(const Point& start_coord=(0,0), const Sint16& w_param=0, const Sint16& h_param=0):_xy_(start_coord), w(w_param), h(h_param){

	}
	Rect(const SDL_Rect& init):_xy_(init.x,init.y),w(init.w),h(init.h){

	}


public:		//METODI SET&GET
	inline void Set_Position(const Point& xy_position){
		this->_xy_=xy_position;
	}
	inline void Set_W(const Sint16& w_param){
		this->w=w_param;
	}
	inline void Set_H(const Sint16& h_param){
		this->h=h_param;
	}
	inline const Point& Get_Position(void) const{
		return this->_xy_;
	}
	inline const Sint16 Get_W(void) const{
		return this->w;
	}
	inline const Sint16 Get_H(void) const{
		return this->h;
	}




public:		//FUNZIONI AGGIUNTIVE STATICHE
	/*Verifica se due Rect sono sovrapposte.
	Ritorna 'true' se la condizione è verificata, altrimenti false*/
	inline static const bool Rect_Collide(const Rect& r1, const Rect& r2){
		if(SDL_CollideBoundingBox(r1, r2)){
			return true;
		}
		return false;
	}

	/*Ritorna l'intersezione tra due rettangoli*/
	inline static const bool Rects_Intersect(const Rect& op1, const Rect& op2, Rect& _out_result){
		if(Rect::Rect_Collide(op1,op2)==true) {  
			_out_result._xy_.Set_X(Point::Rts_Max(op1._xy_.Get_X(), op2._xy_.Get_X()));
			_out_result._xy_.Set_Y(Point::Rts_Max(op1._xy_.Get_Y(), op2._xy_.Get_Y()));
			_out_result.w = Point::Rts_Min( op1._xy_.Get_X() + op1.w, op2._xy_.Get_X() + op2.w) - _out_result._xy_.Get_X();
			_out_result.h = Point::Rts_Min( op1._xy_.Get_Y() + op1.h, op2._xy_.Get_Y() + op2.h) - _out_result._xy_.Get_Y();
			return true;
		} 
		_out_result._xy_.Set_X(0);
		_out_result._xy_.Set_Y(0);
		_out_result.w=0;
		_out_result.h=0;
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

	Rect operator+(const Rect& oth) const{
		return Rect(this->_xy_ + oth._xy_, this->w + oth.w, this->h + oth.h);
	}

	Rect operator+(const Point& oth) const{
		return Rect(this->_xy_ + oth, this->w, this->h);
	}





private:		//PRIVATE: DATA
	Point _xy_;
	Sint16 w;
	Sint16 h;
};

#endif