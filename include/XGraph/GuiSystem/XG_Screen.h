#ifndef __XG_SCREEN__CONTAINER__GUI
#define __XG_SCREEN__CONTAINER__GUI

#include <XGraph/GuiSystem/XG_Container.h>


class XG_Screen: public XG_Container{
public:		//INTERFACCIA COMPONENT
	virtual const bool Load(XG_Container* =NULL);
	virtual void UnLoad(void);
	virtual const bool Is_Load(void) const{
		return OutVideo::Get_Instance().Is_Load();
	}
	virtual const int Get_W(void) const{
		return OutVideo::Get_Instance().Get_W_Screen();
	}
	virtual const int Get_H(void) const{
		return OutVideo::Get_Instance().Get_H_Screen();
	}
	virtual void SetAlpha(const Uint8 setter){
		XG_Container::SetAlpha(setter);
	}

public:		//INTERFACCIA COMPONENT (PRIVATA)
	virtual const bool Check_Focus(const XG_Event_Input& _event){
		return XG_Container::Check_Focus(_event);
	}

public:		//SINGLETON ACCESS
	inline static XG_Screen& Get_Instance(void){
		if(XG_Screen::mpInstance==NULL){
			XG_Screen::mpInstance = new XG_Screen();
			assert(XG_Screen::mpInstance);
		}
		return *XG_Screen::mpInstance;
	}
private:	//SINGLETON DATA
	static XG_Screen* mpInstance;
	XG_Screen(void);
	XG_Screen(const XG_Screen&);
	XG_Screen& operator=(const XG_Screen&);
};

#define Desktop XG_Screen::Get_Instance()

#endif