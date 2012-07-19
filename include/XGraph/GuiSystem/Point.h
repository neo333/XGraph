#ifndef __POINT__GUI
#define __POINT__GUI


#include <SDL/SDL.h>
#include <cmath>
#include <XGraph/_begin.h>

class XGRAPH_DLLAPI Point{
private:		//PRIVATE: DATA
	Sint16 x;
	Sint16 y;


public:		//COSTRUTTORE
	Point(const Sint16 x_param =0, const Sint16 y_param =0): x(x_param), y(y_param){

	}


public:		//METODI SET&GET
	void Set_X(const Sint16 x_param){
		this->x=x_param;
	}
	void Set_Y(const Sint16 y_param){
		this->y=y_param;
	}
	const Sint16 Get_X(void) const{
		return this->x;
	}
	const Sint16 Get_Y(void) const{
		return this->y;
	}



public:		//OPERATORI
	const double Module(void) const{
		return sqrt((double)((this->x*this->x) + (this->y*this->y)));
	}
	const bool operator!=(const Point& oth)const{
		if(this->x!=oth.x) return true;
		if(this->y!=oth.y) return true;
		return false;
	}

	Point operator+(const Point& oth) const{
		Point rts=*this;
		rts.x+=oth.x;
		rts.y+=oth.y;
		return rts;
	}
	Point operator-(const Point& oth) const{
		Point rts=*this;
		rts.x-=oth.x;
		rts.y-=oth.y;
		return rts;
	}



public:		//FUNZIONI STATICHE aggiuntive
	/*Ritorna il massimo tra i due elementi espressi nel parametro*/
	template<class T> static T& Rts_Max(T& elem1, T& elem2){
		if(elem1>elem2) return elem1;
		return elem2;
	}

	/*Ritorna il minimo tra i due elementi espressi nel parametro*/
	template<class T> static T& Rts_Min(T& elem1, T& elem2){
		if(elem1<elem2) return elem1;
		return elem2;
	}













};

#endif