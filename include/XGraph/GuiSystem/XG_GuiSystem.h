#ifndef __XG_GUI_SYSTEM__GUI
#define __XG_GUI_SYSTEM__GUI

#include <XGraph/GuiSystem/XG_Event_Input.h>
#include <XGraph/GuiSystem/XG_Container.h>
#include <cassert>

class XG_GuiSystem{
public:		//INTERFACCIA CLIENT
	const bool Run(void);




private:	//FUNZIONI GESTIONE INTERNE
	const bool UpDateAllInput(void);

private:	//DATA
	XG_Event_Input last_input;
	bool m_left_but;
	bool m_right_but;
	bool m_middle_but;
	std::string _last_error;


public:		//SINGLETON ACCESSO
	inline static XG_GuiSystem& Get_Instance(void){
		if(XG_GuiSystem::mpInstance==NULL){
			XG_GuiSystem::mpInstance=new XG_GuiSystem();
			assert(XG_GuiSystem::mpInstance);
		}
		return *XG_GuiSystem::mpInstance;
	}
private:	//SINGLETON REALIZZAZIONE
	static XG_GuiSystem* mpInstance;
	XG_GuiSystem(void);
	XG_GuiSystem(const XG_GuiSystem&);
	XG_GuiSystem& operator=(const XG_GuiSystem&);
};

#define GuiSystem XG_GuiSystem::Get_Instance()

#endif