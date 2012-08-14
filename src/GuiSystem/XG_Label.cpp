#include <XGraph/GuiSystem/XG_Label.h>

void XG_Label::FormatString(void){
	if(this->loaded==true){
		std::vector<std::string> _form;
		_form.reserve(this->lines.size());
	

		/*formatto i caratteri di new line*/
		size_t find_curs,pos_start=0;
		do{
			find_curs=this->text_extend.find('\n',pos_start);
			if(find_curs!=std::string::npos){
				_form.push_back(this->text_extend.substr(pos_start,find_curs - pos_start));
				pos_start=find_curs+1;
			}else{
				_form.push_back(this->text_extend.substr(pos_start));
			}
		}while(find_curs!=std::string::npos);
		/**********************************/

		/*formatto la dimensione massima*/
		if(this->w_limit>0){
			//TODO!
		}
		/********************************/


		/*effettuo il redering del tutto*/
		size_t dim_after=this->lines.size();
		size_t dim_next=_form.size();
		this->lines.resize(dim_next,Text(std::string(),this->mycolor));
		for(size_t i=dim_after; i<dim_next; i++){
			this->lines[i].Set_Font(this->myfont);
			this->lines[i].Set_ModeRender(this->mymode);
		}
		std::string* ref_str;
		Text* ref_txt;
		for(size_t i=0; i<dim_next; i++){
			ref_str=&_form[i];
			ref_txt=&this->lines[i];

			ref_txt->Set_Text(*ref_str);
			ref_txt->Set_Alpha(this->myalpha);

			if(ref_txt->Get_Widht() > this->w_max_lines){
				this->w_max_lines=ref_txt->Get_Widht();
			}
		}

		/********************************/
	}else{
		this->lines.clear();
		this->w_max_lines=0;
	}
	this->lines_num=this->lines.size();
}