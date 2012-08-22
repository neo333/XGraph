#ifndef __XG_TEXT_BOX__WIDGET
#define __XG_TEXT_BOX__WIDGET

#include <XGraph/GuiSystem/XG_Component.h>
#include <XGraph/GuiSystem/XG_FontSys.h>
#include <SDL/SDL_gfxPrimitives.h>
#include <XGraph/InputSystem/Tastiera.h>
#include <XGraph/GuiSystem/XG_Container.h>

class XG_TextBox: public XG_Component{
public:		//COSTRUTTORE
	XG_TextBox(const std::string& init_str =std::string()):XG_Component(),data(std::string(),Color(0,0,0)),active(false),
		pos_cursore(0),time_mem_delay_cursore(0),vis_cursore(false){
		data.Set_Font(XGRAPH_FONTSYS_2);
		this->info_text.Set_Font(XGRAPH_FONTSYS_2);
		this->info_text.Set_Color(Color(100,100,100));
		this->info_text.Set_ModeRender(XGRAP_MODE_RENDER_TEXT_QUALITY);
		this->Set_Size(0,0);
		this->Set_Text(init_str);
		this->data.Set_ModeRender(XGRAP_MODE_RENDER_TEXT_QUALITY);
	}

public:		//CARICAMENTO
	virtual const bool Load(XG_Container* =NULL);
	virtual void UnLoad(void){
		XG_Component::UnLoad();
		this->render_back.UnLoad();
		this->cursore.UnLoad();
		this->data.Set_Text("");
		this->w=0;
		this->h=0;
	}

	void Set_Size(const int w_size, const int h_size =0){
		if(w_size==this->w && h_size==this->h) return;
		this->w=w_size;
		this->h=h_size;
		if(this->h==0){
			if(this->data.Get_Font()){
				this->h=this->data.Get_Font()->Get_H_Font();
			}
		}
		if(this->w < XG_TextBox::w_corner*2+1){
			this->w = XG_TextBox::w_corner*2+1;
		}
		if(this->h < XG_TextBox::h_corner*2+1){
			this->h = XG_TextBox::h_corner*2+1;
		}
		if(this->render_back.Is_Load()){
			this->UpDate_Render();
		}
	}

public:		//METODI SET&GET
	virtual const int Get_W(void) const{
		return this->w;
	}
	virtual const int Get_H(void) const{
		return this->h;
	}
	const std::string& Get_Text(void) const{
		return this->data.Get_Text();
	}

	virtual void SetAlpha(const Uint8 setter){
		this->render_back.Set_Alpha(setter);
	}
	void Set_Text(const std::string& setter){
		this->data.Set_Text(setter);
	}
	void Set_ModeCryp(const bool setter){
		this->data.Set_CrypMode(setter);
	}
	void Set_InfoText(const std::string& setter){
		this->info_text.Set_Text(setter);
	}






protected:	//CONTROLLO & DISEGNO
	virtual const bool Check_Focus(const XG_Event_Input& _event){
		if(_event._mouseclic.bottone==XG_Event_Input::LEFT && XG_Component::Point_inArea(_event._mouseclic.xy,Rect(this->Get_AbsolutePosition(),this->Get_W(),this->Get_H()))==true && this->Get_Container()->Is_InFocus()==true){
			this->pos_cursore=this->data.Get_Text().size();
			this->active=true;
			return true;
		}else{
			if(_event==true && _event._key_press_instant.press==false){
				this->active=false;
			}
		}
		if(this->active==true){
			return true;
		}
		return false;
	}
	virtual void Exeque_Controll(const XG_Event_Input& _event){
		if(_event._key_press_instant.press==true){
			Uint16 unicode_char=_event._key_press_instant.unicode_key;
			if(unicode_char==0){
				const Uint8* key_state=Tastiera::Get_Instance().Get_snapState_Key();
				if(key_state[SDLK_LEFT]){
					if(this->pos_cursore>0){
						this->pos_cursore--;
					}
				}else{
					if(key_state[SDLK_RIGHT]){
						if(this->pos_cursore<this->data.Get_Text().size()){
							this->pos_cursore++;
						}
					}
				}
			}else{
				std::string new_text=this->data.Get_Text();
				if((unicode_char >= 0x20 && unicode_char <= 0x7E) || (unicode_char >= 0xC0 && unicode_char <= 0xFF)){
					if(this->data.Get_Widht() + Text::Get_Size_Pixel_String("OK",*this->data.Get_Font()).Get_W() < this->Get_W()){
						new_text.insert(new_text.begin() + this->pos_cursore,(unsigned char)(unicode_char));
						this->pos_cursore+=1;
					}
				}else{
					if(unicode_char==0x08 && new_text.size()>0 && this->pos_cursore>0){
						new_text.erase(new_text.begin() + this->pos_cursore -1);
						this->pos_cursore-=1;
					}
				}
				this->Set_Text(new_text);
			}
		}
	}
	virtual const bool Drawn_Component(void){
		this->render_back.Set_Position(this->Get_AbsolutePosition());
		this->render_back.SetDrawnableArea(this->Get_DrawnableAreaAbsolute());
		this->data.Set_Position(this->Get_AbsolutePosition() + Point(5,this->h/2 - this->data.Get_Height()/2));
		this->data.SetDrawnableArea(this->Get_DrawnableAreaAbsolute() - Rect(this->Get_AbsolutePosition(),this->w,this->h));
		this->info_text.Set_Position(this->Get_AbsolutePosition() + Point(5,this->h/2 - this->info_text.Get_Height()/2));
		this->info_text.SetDrawnableArea(this->Get_DrawnableAreaAbsolute() - Rect(this->Get_AbsolutePosition(),this->w,this->h));

		if(this->render_back.Drawn()==false){
			this->AddError_toLOG(this->render_back.Get_LastError());
			return false;
		}

		if(this->data.Get_Text().size()==0){
			if(this->info_text.Drawn()==false){
				this->AddError_toLOG(this->info_text.Get_LastError());
				return false;
			}
		}

		if(this->data.Drawn()==false){
			this->AddError_toLOG(this->data.Get_LastError());
			return false;
		}

		if(this->active){
			Uint32 time_cur=SDL_GetTicks();
			bool _swap=false;
			if(time_cur - this->time_mem_delay_cursore>=XG_TextBox::delay_cursore){
				this->time_mem_delay_cursore=time_cur;
				_swap=true;
			}

			if(this->vis_cursore==true){
				this->cursore.Set_Position(this->Get_AbsolutePosition() + Point(5 + Text::Get_Size_Pixel_String(this->data.Get_Text().substr(0,this->pos_cursore),*this->data.Get_Font(),this->data.Get_CrypMode()).Get_W(), this->h/2 - this->cursore.Get_Height()/2));
				this->cursore.SetDrawnableArea(this->Get_DrawnableAreaAbsolute() - Rect(this->Get_AbsolutePosition(),this->w,this->h));

				if(this->cursore.Drawn()==false){
					return false;
				}
				if(_swap){
					this->vis_cursore=false;
				}
			}else{
				if(_swap){
					this->vis_cursore=true;
				}
			}

		}

		return true;
	}










private:	//DATA
	Image render_back;
	Image cursore;
	int w;
	int h;
	Text data;
	bool active;
	unsigned int pos_cursore;
	Uint32 time_mem_delay_cursore;
	bool vis_cursore;
	Text info_text;

private:	//DATA STATIC
	static const Sint16 w_corner;
	static const Sint16 h_corner;
	static const Uint32 delay_cursore;


private:	//FUNC_INT
	const bool UpDate_Render(void);
};


#endif