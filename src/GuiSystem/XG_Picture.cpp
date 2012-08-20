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