#ifndef __COMPONENT__GUI
#define __COMPONENT__GUI

#include <string>
#include <XGraph/GuiSystem/Image.h>
#include <XGraph/GuiSystem/Text.h>
#include <XGraph/GuiSystem/XG_Event_Input.h>
#include <XGraph/InputSystem/Mouse.h>

class XG_Container;
class XG_GuiSystem;

class XG_Component{
public:		//COSTRUTTORE & DISTRUTTORE
	XG_Component(void):xgContainer_handler(NULL),moveable(false),agganciato(false),force_close(false){
		this->Set_Visibile(true);
	}
	virtual ~XG_Component(void){
		if(this->Is_Load()==true){
			this->UnLoad();
		}
	}
public:		//INTERFACCIA	UTENTE
	virtual const bool Load(XG_Container* =NULL);		//<<<-----
	virtual void UnLoad(void);							//		  |
	virtual const int Get_W(void) const=0;				//		  |---FUNZIONI VIRTUALI DA SPECIALIZZARE
	virtual const int Get_H(void) const=0;				//		  |
	virtual void SetAlpha(const Uint8) =0;				//<<<-----

	virtual const bool Is_Load(void) const{
		if(this->xgContainer_handler) return true;
		return false;
	}
	inline void Set_Position_Relative(const Point& setter){
		this->xy_relative_position=setter;
	}
	inline const Point& Get_Position_Relative(void) const{
		return this->xy_relative_position;
	}
	inline void Set_Visibile(const bool setter){
		this->visible=setter;
	}
	inline void Set_Moveable(const bool setter){
		this->moveable=setter;
	}
	inline const std::string& Get_LogError(void) const{
		return this->_logError;
	}
	inline const XG_Container* Get_Container(void) const{
		return this->xgContainer_handler;
	}

	/*Ritorna 'true' se l'oggetto si trova in un CONTAINER (contenitore) che è in focus,
	o 'top'*/
	const bool Object_onTop(void) const;

protected:	//INTERFACCIA INTERNA	(LEGGERE! DA RISPETTARE!!)
	inline const Point& Get_AbsolutePosition(void) const{	//ritorna le coordinate assolute dell'oggetto
		return this->xy_absolute_position_on_screen;		//questa funzione va chiamata dagli oggetti implementati
															//per eseguire le operazioni di disegno
	}
	inline const Rect& Get_DrawnableAreaAbsolute(void) const{		//ritorna l'area di disegno nel quale è possibile
		return this->drawable_area_total;					//disegnare il componente.
															//questa funzione va chiamata ad ogni operazione di disegno
	}
	inline void Set_AreaGrappableRelative(const Rect& setter){		//questa funzione setta l'area RELATIVA
		this->area_grappable=setter;								//dove è possibile cliccare sull'oggetto per trascinarlo
																	//questa funzione andrebbe chiamata ad ogni dimensionamento
																	//dell'oggetto
	}
	inline void AddError_toLOG(const std::string& line){
		this->_logError+=line;
		this->_logError+="\n";
	}

protected:	//CONTROLLO & DISEGNO
	virtual const bool Check_Focus(const XG_Event_Input& _event){
		/*
				Check focus è una funzione deve ritornare 'TRUE' se il componente RICHIEDE l'aggiornamento
				dei controlli (funzione EXEQUE_CONTROLL). altrimenti ritornetà 'FALSE' e in quel caso l'aggiornamento
				dei controlli non verrà eseguito (ma solo la funzione di disegno).

				Questa funzione verrà chiamata SEMPRE a RUN-LOOP!
		*/
		if(moveable==true){
			if(this->agganciato==true){
				return true;
			}else{
				if(_event._mousepress.bottone==XG_Event_Input::LEFT && XG_Component::Mouse_inArea(this->area_grappable + this->Get_AbsolutePosition())){
					this->agganciato_point.Set_X(Mouse::Get_Instance().Get_X());
					this->agganciato_point.Set_Y(Mouse::Get_Instance().Get_Y());
					this->agganciato=true;
					return true;
				}
			}
		}else{
			this->agganciato=false;
		}
		return false;
	}
	virtual void Exeque_Controll(const XG_Event_Input& _event){
		this->UpDateTrascinamento(_event);
	}
	virtual const bool Drawn_Component(void) =0;		//Funzione di disegno chiamato a RUN-LOOP
														//sempre, ammenoché la visibilità dell'oggetto sia 'FALSE'

protected:	//DATI INTERNI
	Point xy_relative_position;







protected:		//FUNZIONI STATICHE DI SUPPORTO
	/*Funzione per la costruzione di un componente grafico usando l'algoritmo di costruzione 'Matrice3x3'*/
	static const bool CompositeObjectGraphic(const Texture& source, const Sint16 w_corner, const Sint16 h_corner, 
		const Sint16 w_size, const Sint16 h_size, Image& _out);
	

	inline void UpDateTrascinamento(const XG_Event_Input& _in){
		/*UPDATE TRASCINAMENTO!*/
		if(this->agganciato==true){
			if(Mouse::Get_Instance().GetState_LeftButton()==false || XG_Component::Mouse_inArea(this->Get_DrawnableAreaAbsolute())==false){
				this->agganciato=false;
			}else{
				Point mouse_point(Mouse::Get_Instance().Get_X(),Mouse::Get_Instance().Get_Y());
				this->Set_Position_Relative(this->Get_Position_Relative() + (mouse_point - this->agganciato_point));
				this->agganciato_point=mouse_point;
			}
		}
	}


	inline static const bool Mouse_inArea(const Rect& area){
		/*Ritorna 'true' se il Mouse si trova nell'area indicata.
		Funzione REAL-TIME!*/
		return XG_Component::Point_inArea(Point(Mouse::Get_Instance().Get_X(),Mouse::Get_Instance().Get_Y()),area);
	}

	inline static const bool Point_inArea(const Point& point, const Rect& area){
		const Sint16& x_p=point.Get_X();	
		const Sint16& y_p=point.Get_Y();	
															
		const Sint16& x_r=area.Get_Position().Get_X();
		const Sint16& y_r=area.Get_Position().Get_Y();
		const Sint16& w_r=area.Get_W();
		const Sint16& h_r=area.Get_H();
		
		if(x_p >= x_r && x_p <= x_r + w_r){
			if(y_p >= y_r && y_p <= y_r + h_r){
				return true;
			}
		}
		return false;
	}
private:		//DATI PRIVATI
	friend class XG_Container;
	friend class XG_GuiSystem;
	bool visible;
	Point xy_absolute_position_on_screen;		//coordinate di posizione dell'oggetto assolute.
												//vengono settate dal container
	XG_Container* xgContainer_handler;			//puntatore al contenitore associato
	Rect drawable_area_total;					//area di disengo settata dal conteiner
	virtual void SubDrawnableAreaTOTAL(const Rect& setter){
		Rect _result;
		Rect::Rects_Intersect(this->drawable_area_total,setter,_result);
		this->drawable_area_total=_result;
	}
	virtual void SetDrawnableAreaTOTAL(const Rect& setter){
		this->drawable_area_total=setter;
	}
	Rect area_grappable;						//area di grap
	std::string _logError;						//log di errore
	bool moveable;
	bool agganciato;
	Point agganciato_point;
	bool force_close;
};

#endif