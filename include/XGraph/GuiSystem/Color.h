#ifndef __COLOR__GUI
#define __COLOR__GUI

#include <SDL/SDL.h>
#include <XGraph/_begin.h>

class XGRAPH_DLLAPI Color{
private:
	Uint8 r;
	Uint8 g;
	Uint8 b;
public:
	Color(const Uint8& r_loc=0, const Uint8& g_loc=0, const Uint8& b_loc=0):r(r_loc),g(g_loc),b(b_loc){

	}

	const Uint8& Get_Red(void) const{
		return this->r;
	}
	const Uint8& Get_Green(void) const{
		return this->g;
	}
	const Uint8& Get_Blue(void) const{
		return this->b;
	}

	operator SDL_Color(void) const{
		SDL_Color rts;
		rts.r=this->r;
		rts.g=this->g;
		rts.b=this->b;
		return rts;
	}

	const bool operator==(const Color& oth) const{
		if(this->r==oth.r && this->g==oth.g && this->b==oth.b){
			return true;
		}
		return false;
	}
	const bool operator!=(const Color& oth) const{
		if(*this==oth){
			return false;
		}
		return true;
	}
};

#endif