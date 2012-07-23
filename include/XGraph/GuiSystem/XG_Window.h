#ifndef __XG_WINDOW_CONTAINER
#define __XG_WINDOW_CONTAINER

#include <XGraph/GuiSystem/XG_Container.h>

struct VertexMatrix{
	Point _position;
	Rect _cutArea;

	VertexMatrix(const Point& set_point, const Rect& set_cut_area):_position(set_point),_cutArea(set_cut_area){

	}
};

typedef std::vector<VertexMatrix> vectorImageVertex;
typedef std::vector<vectorImageVertex> matrixImageVertex;

class XG_Window: public XG_Container{
public:		//COSTRUTTORE
	XG_Window(const Sint16 Wsize, const Sint16 Hsize):XG_Container(){
		this->Set_Size(Wsize,Hsize);
	}

public:		//METODI SET&GET
	virtual void Set_Size(const Sint16 Wsize, const Sint16 Hsize){
		if(Wsize==this->pos_and_size.Get_W() && Hsize==this->pos_and_size.Get_H()) return;

		if(Wsize > XG_Window::w_corner*2){
			this->pos_and_size.Set_W(Wsize);
		}else{
			this->pos_and_size.Set_W(XG_Window::w_corner*2+1);
		}

		if(Hsize > XG_Window::h_corner*2){
			this->pos_and_size.Set_H(Hsize);
		}else{
			this->pos_and_size.Set_H(XG_Window::h_corner*2+1);
		}

		this->RenderWindow();
	}
	virtual void Set_Position(const Point& setter){
		if(setter!=this->pos_and_size.Get_Position()){
			XG_Component::Set_Position(setter);
			this->_renderized.Set_Position(setter);
		}
	}

private:		//DATA
	matrixImageVertex compositeImages;
	std::string title_window;
	Sint16 _wsize_matrix;
	Sint16 _hsize_matrix;
	Image _renderized;


protected:		//IMPLEMENTAZIONE INTERFACCIA
	virtual const bool DrawThisComponent(void){
		return this->_renderized.Drawn();
	}
	virtual void SetDrawnableArea(const Rect&);

private:		//FUNZIONI PRIVATE
	void RenderWindow(void);

	void UpDateMiddleSize(void);
	void ManagerMatrix(void);
	void UpdatePositionMatrix(void);

private:		//COSTANTI DI CLASSE
	static const Sint16 w_corner;
	static const Sint16 h_corner;
};

#endif