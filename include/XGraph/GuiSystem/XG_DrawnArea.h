#ifndef __XG_DRAWN_AREA__CONTAINER
#define __XG_DRAWN_AREA__CONTAINER

#include <XGraph/GuiSystem/XG_Container.h>

class XG_DrawnArea: public XG_Container{
public:		//COSTRUZIONE
	XG_DrawnArea(const Rect& init_area =Rect()):XG_Container(){
		this->Set_NoPriority(true);
		this->Set_Area(init_area);
	}

public:		//GET&SET
	void Set_Area(const Rect& set_area){
		XG_Container::Set_ActiveAreaRelative(set_area);
		this->Set_AreaGrappableRelative(set_area);
		this->area=set_area;
	}
	const Rect& Get_Area(void) const{
		return this->area;
	}
	virtual const int Get_W(void) const{
		return this->area.Get_W();
	}
	virtual const int Get_H(void) const{
		return this->area.Get_H();
	}
	virtual void SetAlpha(const Uint8 setter){
	}

private:	//DATA
	Rect area;
};

#endif