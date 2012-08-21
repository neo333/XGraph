#include <XGraph/GuiSystem/XG_Picture.h>

void XG_Picture::Start_Alpha_Animation(const Uint8 set, const Uint32 delay_set){
	this->Stop_Alpha_Animation();
	this->alpha_anim_diff=set - this->data.Get_Alpha();
	this->delay_alpha_anim=delay_set;
	this->alpha_anim_start=this->data.Get_Alpha();
	this->time_mem_alpha_anim=SDL_GetTicks();
	this->in_anim=true;
}
void XG_Picture::Stop_Alpha_Animation(void){
	this->in_anim=false;
}
const bool XG_Picture::Is_Alpha_Animation_Progress(void) const{
	return this->in_anim;
}

void XG_Picture::UpDate_Animation_Alpha(void){
	if(this->in_anim){
		Uint32 delay_elapse=SDL_GetTicks() - this->time_mem_alpha_anim;
		if(delay_elapse < this->delay_alpha_anim){
			float _eq=(float)(delay_elapse)/(float)(this->delay_alpha_anim)*(float)(this->alpha_anim_diff);
			this->SetAlpha(this->alpha_anim_start + (Uint8)(_eq));
		}else{
			this->SetAlpha(this->alpha_anim_start + this->alpha_anim_diff);
			this->in_anim=false;
		}
		
	}
}






void XG_Picture::Start_Move_Animation(const Point& move_to, const Uint32 delay){
	this->anim_move_pointTO=move_to;
	this->anim_move_pointSTART=this->Get_Position_Relative();
	this->anim_move_delay=delay;
	this->anim_move_process=true;
	this->anim_move_time_to_start=SDL_GetTicks();
}
void XG_Picture::Stop_Move_Animation(void){
	this->anim_move_process=false;
}
const bool XG_Picture::Is_Move_Animation_Progress(void) const{
	return this->anim_move_process;
}


void XG_Picture::UpDate_Animation_Move(void){
	if(this->anim_move_process){
		Uint32 delay_elapse=SDL_GetTicks() - this->anim_move_time_to_start;
		if(delay_elapse < this->anim_move_delay){
			float percent=(float)(delay_elapse)/(float)(this->anim_move_delay);
			float x_diff=(float)(this->anim_move_pointTO.Get_X()) - (float)(this->anim_move_pointSTART.Get_X());
			float y_diff=(float)(this->anim_move_pointTO.Get_Y()) - (float)(this->anim_move_pointSTART.Get_Y());
			x_diff*=percent;
			y_diff*=percent;

			this->Set_Position_Relative(this->anim_move_pointSTART + Point((int)(x_diff),(int)(y_diff)));
		}else{
			this->Set_Position_Relative(this->anim_move_pointTO);
			this->anim_move_process=false;
		}
	}
}