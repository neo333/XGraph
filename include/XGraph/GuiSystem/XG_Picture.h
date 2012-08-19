#ifndef __XG_PICTURE__WIDGET
#define __XG_PICTURE__WIDGET

#include <XGraph/GuiSystem/XG_Component.h>

class XG_Picture: public XG_Component{
public:		//COSTRUZIONE
	XG_Picture(void):XG_Component(),load_parent_call(false){

	}

public:		//LOADING
	const bool LoadImage_fromHD(const std::string& packname, const std::string& filename, const bool keycolor =true){
		/*Carica la picture da un file immagine memorizzato sull'hardisk.
		NOTA: Prima di chiamare questa funzione chiamare la funzione 'Load' del widget! altrimenti il programma darà
		un'assserzione di errore*/

		bool status=true;
		assert(this->load_parent_call);
		this->Load(const_cast<XG_Container*>(this->Get_Container()));
		status=data.Load(packname,filename,keycolor);
		this->UpDateMetricImage();
		return status;
	}
	const bool LoadImage_fromMemory(void* memory_area, const long& area_memory_size, const bool keycolor =true){
		/*Carica la picture da un'area di memoria.
		NOTA: Prima di chiamare questa funzione chiamare la funzione 'Load' del widget! altrimenti il programma darà
		un'assserzione di errore*/

		assert(this->load_parent_call);
		bool status=true;
		this->Load(const_cast<XG_Container*>(this->Get_Container()));
		status= data.Load_fromMemory(memory_area,area_memory_size,keycolor);
		this->UpDateMetricImage();
		return status;
	}
	virtual const bool Load(XG_Container* handle=NULL){
		this->load_parent_call=true;
		return XG_Component::Load(handle);
	}
	virtual void UnLoad(void){
		XG_Component::UnLoad();
		this->data.UnLoad();
	}

public:		//METODI GET&SET
	virtual const int Get_W(void) const{
		return this->data.Get_Widht();
	}
	virtual const int Get_H(void) const{
		return this->data.Get_Height();
	}
	virtual void SetAlpha(const Uint8 setter){
		this->data.Set_Alpha(setter);
	}
	void ResizeImage(const int new_w, const int new_h){
		this->data.ResizeImage(new_w,new_h);
		this->UpDateMetricImage();
	}




protected:	//CONTROLLO&DISEGNO
	virtual const bool Check_Focus(const XG_Event_Input& _event){
		return XG_Component::Check_Focus(_event);
	}
	virtual void Exeque_Controll(const XG_Event_Input& _event){
		XG_Component::Exeque_Controll(_event);
	}
	virtual const bool Drawn_Component(void){
		this->data.Set_Position(this->Get_AbsolutePosition());
		this->data.SetDrawnableArea(this->Get_DrawnableAreaAbsolute());

		if(this->data.Drawn()==false){
			this->AddError_toLOG(this->data.Get_LastError());
			return false;
		}
		return true;
	}

private:	//DATA
	Image data;
	bool load_parent_call;


private:	//METODI INTERNI DI SUPPORTO
	inline void UpDateMetricImage(void){
		this->Set_AreaGrappableRelative(Rect(Point(0,0),this->Get_W(),this->Get_H()));
	}
};

#endif