#include "ExemProject.h"	


int WINAPI _tWinMain(HINSTANCE hInst, HINSTANCE hPrev, LPTSTR lpszCmdLine, int nCmdShow)	
{
	SearchingWrongWords dlg;	
	return DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), NULL, SearchingWrongWords::DlgProc);		
}	
