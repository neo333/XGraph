#ifndef __XG_GUI_SYSTEM__GUI
#define __XG_GUI_SYSTEM__GUI

#include <XGraph/GuiSystem/XG_Event_Input.h>
#include <XGraph/GuiSystem/XG_Container.h>
#include <XGraph/GuiSystem/XG_ContextMenu.h>
#include <cassert>
#include <map>

class XG_GuiSystem{
public:		//INTERFACCIA CLIENT
	const bool Run(void);

	/*NOTA BENE!
	Questa funzione permette di registrare nel sistema un componente dinamico.
	Solitamente componenti allocati in memoria dinamica (es. 'new XG_Window')
	Per evitare di gestire la memoria dinamica, è possibile evitare di deallocare la memoria manualmente
	registrando l'indirizzo del componente con questa funzione.
	Appena il componente in questione verrà 'UnLoad' il sistema provvederà automaticamente a dellocare la risorsa
	
	VINCOLI: il componente registrato DEVE NECESSARIAMENTE essere allocato in memoria heap (dinamica!)*/
	void RegistraComponenteDinamico(XG_Component* obj,const char* namefile, const long linefile){
		if(obj){
			this->dynamic_component.push_back(info_Component_add(obj,namefile,linefile));
		}
	}

















private:	//FUNZIONI ESTERNE DEL SISTEMA
	friend const bool XG_Component::Drawn_Component(void);
	void DisegnaContextMenu(XG_ContextMenu* setter, const Point& xy){
		this->last_context_menu_to_drawn=setter;
		this->xy_last_context_menu_to_drawn=xy;
	}

private:	//FUNZIONI GESTIONE INTERNE
	const bool UpDateAllInput(void);
	void CheckDynamicComponent(void);

private:	//DATA
	XG_Event_Input last_input;
	bool m_left_but;
	bool m_right_but;
	bool m_middle_but;
	std::string _last_error;
	XG_ContextMenu* last_context_menu_to_drawn;
	Point xy_last_context_menu_to_drawn;
	
	struct info_Component_add{
		XG_Component* handle;
		std::string namefile;
		long linefile;
		info_Component_add(XG_Component* const _handle,const std::string& _namefile, const long _line):handle(_handle),namefile(_namefile),linefile(_line){

		}
	};
	typedef std::vector<info_Component_add> LISTA_DINAMICI;
	typedef LISTA_DINAMICI::iterator ITERATORE_DINAMICI;
	LISTA_DINAMICI dynamic_component;


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