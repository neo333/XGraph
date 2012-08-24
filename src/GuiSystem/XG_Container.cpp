#include <XGraph/GuiSystem/XG_Container.h>
#include <XGraph/GuiSystem/XG_GuiSystem.h>

const bool XG_Container::Drawn_Component(void){
	ITERATORE it;
	bool status=true;
	XG_Component* cursor;
	for(it=this->handled_component.begin(); it!=this->handled_component.end(); it++){
		cursor=(*it);
		if(cursor->visible==true){
			if(cursor->Drawn_Component()==false){
				this->AddError_toLOG(cursor->Get_LogError());
				status=false;
			}
		}
	}
	if(XG_Component::Drawn_Component()==false){
		status=false;
	}
	return status;
}

void XG_Container::CancelLastReuquestFocus(void){
	ITERATORE it;
	for(it=this->handled_component.begin(); it!=this->handled_component.end(); it++){
		XG_Container* _cast=XG_Container::TryCastIntoContainer_fromComponent((*it));
		if(_cast){
			_cast->last_request_focus=false;
		}
	}
}