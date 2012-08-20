#ifndef __XGRAPH__LIBRARY
#define __XGRAPH__LIBRARY

#include <XGraph/GuiSystem/OutVideo.h>
#include <XGraph/GuiSystem/Image.h>		//uhmm.. un pò troppo a basso livello!
#include <XGraph/InputSystem/Gestore_Input.h>
#include <XGraph/GuiSystem/XG_GuiSystem.h>

//--CONTENITORI--
#include <XGraph/GuiSystem/XG_Screen.h>
#include <XGraph/GuiSystem/XG_Window.h>
//--------------

//---WIDGETS----
#include <XGraph/GuiSystem/XG_Button.h>
#include <XGraph/GuiSystem/XG_Label.h>
#include <XGraph/GuiSystem/XG_TextBox.h>
#include <XGraph/GuiSystem/XG_Picture.h>
//--------------

//---ELEMENTI_PREFABRICATI---
#include <XGraph/GuiSystem/XG_MessageBox.h>
//---------------------------

#define XGRAPH_MAIN_LOOP_run()	\
			SysInput.UpDateAll();		\
			GuiSystem.Run();			\
			Screen.UpDateScreen();	

#endif