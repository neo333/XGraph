#ifndef __COMPONENT__GUI
#define __COMPONENT__GUI

#include <XGraph/GuiSystem/Image.h>
#include <XGraph/InputSystem/Mouse.h>
#include <string>

class XG_Container;

class XG_Component{
public:		//COSTRUTTORE
	XG_Component(void):moveable(false),agganciato(false),visible(true),active_controll(true){
	}

public:		//INTERFACCIA COMPONENTE GRAFICO
	virtual const bool Load(void) =0;
	virtual void UnLoad(void) =0;
	virtual void SetDrawnableArea(const Rect&) =0;
	virtual const Rect& GetDrawnableArea(void) const=0;
	virtual const bool Is_Load(void) const=0;
	virtual const std::string& Get_LastError(void) const=0;
	virtual void Set_Position(const Point&) =0;
	virtual const Point& Get_Position(void) const =0;
	virtual const Sint16 Get_W(void) const =0;
	virtual const Sint16 Get_H(void) const =0;
	virtual void Set_Alpha(const Uint8) =0;
	virtual void Set_Moveable(const bool setter){
		this->moveable=setter;
	}
	virtual void Set_Visible(const bool setter){
		this->visible=setter;
	}
	virtual inline const bool Get_Visible(void) const{
		return this->visible;
	}
	virtual const bool Get_Moveable(void){
		return this->moveable;
	}
	virtual const bool Run(void){
		if(this->visible==true && this->Is_Load()){
			if(this->active_controll==true){
				this->UpDateControll();
				this->UpdateTrascinaObj();
			}
			return this->Drawn();
		}
		return true;
	}
protected:

	/*Chiama alla funzione di controllo dell'oggetto RUN-LOOP se il componente ha focus*/
	virtual void UpDateControll(void) =0;

	/*Funzione di disegno pura. Viene chiamata a 'RUN-LOOP' se e solo se il componente è settato come 'VISIBILE'.
	Disegna il componente*/
	virtual const bool Drawn(void) =0;


protected:	//FUNZIONI DI SUPPORTO
	/*Costruisce il rendering di un componente grafico utilizzando l'algoritmo della scomposizione di matrice
	(l'immagine del componente sarà composta da 9 parti: angolo alto sinistro, alto centrale, alto destro, centrale sinistro,
	centrale centrale, centrale destro, sotto sinistro, sotto centrale, sotto destro)
	NOTA: per maggiori informazioni leggere il file sorgente (.cpp) associato.*/
	static const bool CompositeObjectGraphic(const Texture& source, const Sint16 w_corner, const Sint16 h_corner, 
		const Sint16 w_size, const Sint16 h_size, Image& _out);

	
	/*Ritorna 'true' se il Mouse si trova all'interno dell'area specificata, altrimenti ritorna 'false'*/
	inline static const bool Mouse_inArea(const Rect& area){
		return XG_Component::Point_inArea(Point(ctrlMouse.Get_X(),ctrlMouse.Get_Y()),area);
	}

	/*Ritorna 'true' se il Punto si trova all'interno dell'area specificata, altrimenti ritorna 'false'*/
	inline static const bool Point_inArea(const Point xy, const Rect& area){
		const Sint16& x_p=xy.Get_X();
		const Sint16& y_p=xy.Get_Y();
		
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

	inline void Set_GrappableArea(const Rect& setter){
		this->area_grappable=setter;
	}

private:	//PRIVATE DATA
	friend class XG_Container;
	bool moveable;
	bool visible;
	bool agganciato;
	Point clic_agganciato;
	bool active_controll;	//blocca i controlli sul componente(viene utilizzato dai container per gestire le priorità di input)
	Rect area_grappable;

private:	//FUNZIONI DI SUPPORTO COMPONENTI
	inline void UpdateTrascinaObj(void){
		if(this->moveable && XG_Component::Mouse_inArea(this->GetDrawnableArea())==true){
			if(this->agganciato){
				if(ctrlMouse.GetState_LeftButton()==false){
					this->agganciato=false;
				}else{
					this->Set_Position(this->Get_Position() + Point(ctrlMouse.Get_X() - this->clic_agganciato.Get_X(), ctrlMouse.Get_Y() - this->clic_agganciato.Get_Y()));
					this->clic_agganciato.Set_X(ctrlMouse.Get_X());
					this->clic_agganciato.Set_Y(ctrlMouse.Get_Y());
				}
			}else{
				if(ctrlMouse.Get_Instance().GetState_LeftButton()==true && XG_Component::Mouse_inArea(this->area_grappable + this->Get_Position())==true){
					this->agganciato=true;
					this->clic_agganciato.Set_X(ctrlMouse.Get_X());
					this->clic_agganciato.Set_Y(ctrlMouse.Get_Y());
				}
			}
		}else{
			this->agganciato=false;
		}
	}
};

#endif