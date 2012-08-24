#ifndef __XG_CONTEXT_MENU__GUI
#define __XG_CONTEXT_MENU__GUI

#include <XGraph/GuiSystem/Image.h>
#include <XGraph/GuiSystem/Text.h>
#include <vector>
#include <string>
#include <XGraph/InputSystem/Mouse.h>

class XG_GuiSystem;

class XG_ContextMenu{
public:		//COSTRUZIONE
	typedef std::vector<std::string> VETT_STRINGS;
	XG_ContextMenu(const VETT_STRINGS& lista_argomenti = VETT_STRINGS()):argomenti(lista_argomenti),loaded(false){

	}
	XG_ContextMenu(const XG_ContextMenu& oth):argomenti(oth.argomenti),loaded(false){
	}
	XG_ContextMenu& operator=(const XG_ContextMenu& oth){
		this->argomenti=oth.argomenti;
		this->loaded=false;
		this->box_render.UnLoad();
		this->argomenti_render.clear();
		return *this;
	}

public:		//GET&SET
	const Sint16 Get_W(void) const{
		return this->box_render.Get_Widht();
	}
	const Sint16 Get_H(void) const{
		return this->box_render.Get_Height();
	}
	const Point& Get_XY(void) const{
		return this->box_render.Get_Position();
	}
	const size_t Get_Number_Label(void) const{
		return this->argomenti.size();
	}


public:		//OPERATORI
	void operator+=(const std::string& adder){
		this->argomenti.push_back(adder);
		this->loaded=false;
	}





private:		//DISEGNO
	friend class XG_GuiSystem;
	const bool Drawn(const Point&);



private:	//DATA
	typedef std::vector<Text> VETT_TEXT;

	VETT_STRINGS argomenti;

	Image box_render;
	VETT_TEXT argomenti_render;
	bool loaded;
		void MakeRender(void);
	static const Sint16 w_corner;
	static const Sint16 h_corner;
	static const Sint16 interline;
	static const Color label_non_select;
	static const Color label_select;
};

#endif