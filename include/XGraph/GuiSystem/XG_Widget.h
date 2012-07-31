#ifndef __WIDGET__GUI
#define __WIDGET__GUI

#include <XGraph/GuiSystem/XG_Component.h>
#include <XGraph/GuiSystem/XG_Evento.h>


class XG_Widget: public XG_Component{
public:		//INTERFACCIA COMPONENTE GRAFICO
	virtual const bool Load(void) =0;
	virtual void UnLoad(void) =0;
	virtual void SetDrawnableArea(const Rect&) =0;
	virtual const bool Is_Load(void) const=0;
	virtual const std::string& Get_LastError(void) const=0;
	virtual void Set_Position(const Point&) =0;
	virtual const Point& Get_Position(void) const =0;
	virtual const Sint16 Get_W(void) const =0;
	virtual const Sint16 Get_H(void) const =0;
protected:
	virtual void UpDateControll(void) =0;
	virtual const bool Drawn(void) =0;
};


#endif