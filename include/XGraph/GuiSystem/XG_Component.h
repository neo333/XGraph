#ifndef __COMPONENT__GUI
#define __COMPONENT__GUI

#include <XGraph/GuiSystem/Point.h>
#include <XGraph/GuiSystem/Image.h>

class XG_Component{
public:		//METODI SET&GET
	virtual void Set_Position(const Point& setter){
		this->pos_and_size.Set_Position(setter);
	}
	virtual const Point& Get_Position(void) const{
		return this->pos_and_size.Get_Position();
	}
	virtual void Set_Size(const Sint16 wSize, const Sint16 hSize){
		this->pos_and_size.Set_W(wSize);
		this->pos_and_size.Set_H(hSize);
	}
	virtual const Sint16 Get_Wsize(void) const{
		return this->pos_and_size.Get_W();
	}
	virtual const Sint16 Get_Hsize(void) const{
		return this->pos_and_size.Get_H();
	}



private:		//FUNZIONI VIRTUALI (INTERFACCIA COMPONENTE)
	friend class XG_Container;
	virtual const bool DrawThisComponent(void)=0;
	virtual void SetDrawnableArea(const Rect&)=0;



protected:	//DATA
	Rect pos_and_size;		//Posizione e dimensione del componente grafico
};

#endif