#ifndef __XG_FONT_SYS__GUI
#define __XG_FONT_SYS__GUI

#include <XGraph/GuiSystem/Font.h>
#include <cassert>

class XG_FontSys{
public:		//ACCESSO AI FONT DI SISTEMA
	inline Font& Get_fontSYS_1(void){
		return this->sysFont1;
	}






private:	//DATA FONT SYSTEMA
	Font sysFont1;


public:		//ACCESSO SINGLETON
	inline static XG_FontSys& Get_Instance(void){
		if(XG_FontSys::pmInstance==NULL){
			XG_FontSys::pmInstance=new XG_FontSys();
			assert(XG_FontSys::pmInstance);
		}
		return *XG_FontSys::pmInstance;
	}
private:	//REALIZE SINGLETON
	static XG_FontSys* pmInstance;
	XG_FontSys(void);
	XG_FontSys(const XG_FontSys&);
	XG_FontSys& operator=(const XG_FontSys&);
};

#define XGRAPH_FONTSYS_1 XG_FontSys::Get_Instance().Get_fontSYS_1()

#endif