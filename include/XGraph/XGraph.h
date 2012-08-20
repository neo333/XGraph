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


//---MACRO LIBRERIA----------------------------

/*Aggiorna tutti gli input, disegna tutti i componenti grafici e li aggiorna nel controllo, poi
esegue il blit finale dello schermo a video*/
#define XGRAPH_MAIN_LOOP_run()	\
			SysInput.UpDateAll();		\
			GuiSystem.Run();			\
			Screen.UpDateScreen();	






/*'Ritorna' (creando) un nuovo oggetto 'EVENTO' da inserire nei controlli dei widget.
Richiede un puntatore a funzione, il puntatore del componente chiamante e il puntatore dell'oggetto
sul quale esegue l'azione della funzione*/
#define NEWEVENT(FUNZ,CALLER,OPERAND) XG_Event<XG_Component>(FUNZ,CALLER,OPERAND)






/*Crea un nuovo MessageBox di tipo NORMAL*/
#define New_MessageBox(TITLE,MESSAGE) \
			NewComponent(new XG_MessageBox(TITLE,MESSAGE,XGRAPH_MESSAGEBOX_TYPE_NORMAL,NULL));

/*Crea un nuovo MessageBox di tipo definito dall'utente, specificando il puntatore di memoria
dove memorizzare il risultato del messagebox*/
#define New_MessageBox_plus(TITLE,MESSAGE,TYPE,RESULT_POINTER) \
			NewComponent(new XG_MessageBox(TITLE,MESSAGE,TYPE,RESULT_POINTER));




/*Forza la chiusura dell'applicazione, lasciando eventualmente un messaggio*/
#define XGraph_CloseApplication(MESSAGE)	Gestore_Input::Get_Instance().Set_ForceCloseApp(MESSAGE)



/*Avvia ed esegue a loop tutte le procedure di controllo e disegno finché l'applicazione
non viene terminata da un evento di chiusura interno.*/
#define XGRAPH_MAINLOOP()	\
	while(Gestore_Input::Get_Instance().Check_ExitApp()==false){	\
		XGRAPH_MAIN_LOOP_run();										\
	}


/*Avvia ed esegue a loop tutte le procedure di controllo e disegno finché l'applicazione
non viene terminata da un evento di chiusura interno.
Inoltre viene eseguita l'istruzione (o più) indicate nel parametro della macro prima di eseguire
tutti i controlli e il disegno*/
#define XGRAPH_MAINLOOP_plus(ISTRUZIONE)	\
	while(Gestore_Input::Get_Instance().Check_ExitApp()==false){	\
		ISTRUZIONE														\
		XGRAPH_MAIN_LOOP_run();										\
	}

//----------------------------------------------

#endif