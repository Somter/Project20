#pragma once
#include "header.h"

class SearchingWrongWords	
{
public:
	SearchingWrongWords(void);	
public:
	~SearchingWrongWords(void);
	static INT_PTR CALLBACK DlgProc(HWND hWnd, UINT mes, WPARAM wp, LPARAM lp);	
	static SearchingWrongWords* ptr;
	void Cls_OnClose(HWND hwnd);
	BOOL Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam);
	void Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify);
	void Cls_OnSize(HWND hwnd, UINT state, int cx, int cy);	
	void OnTrayIcon(WPARAM wp, LPARAM lp); 
	void Cls_OnTimer(HWND hwnd, UINT id);		
	HWND hButton4, hButton5, hButton2, hButton3, hEdit1, hList1, hList2, hProgress;	
	HICON hIcon;		
	PNOTIFYICONDATA pNID;	
	int current = 0;	
};
