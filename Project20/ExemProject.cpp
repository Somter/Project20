#include "ExemProject.h"
std::vector<TCHAR*> wordArray;	

SearchingWrongWords* SearchingWrongWords::ptr = NULL;

SearchingWrongWords::SearchingWrongWords(void)
{
	ptr = this;	
	pNID = new NOTIFYICONDATA;	
}

SearchingWrongWords::~SearchingWrongWords(void)
{
	delete pNID;	
	for (size_t i = 0; i < wordArray.size(); ++i) {	
		delete[] wordArray[i];		
	}
}

void SearchingWrongWords::Cls_OnClose(HWND hwnd)
{
	EndDialog(hwnd, 0);
}

BOOL SearchingWrongWords::Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam)
{
	hEdit1 = GetDlgItem(hwnd, IDC_EDIT1);

	hList1 = GetDlgItem(hwnd, IDC_LIST1);
	hList2 = GetDlgItem(hwnd, IDC_LIST2);	

	hButton4 = GetDlgItem(hwnd, IDC_BUTTON4);
	hButton5 = GetDlgItem(hwnd, IDC_BUTTON5);	
		
	return TRUE;
}

struct FileName {
	std::wstring word;
	std::wstring name;
};

void SearchWords(const std::wstring& directory, HWND hList2) {
	WIN32_FIND_DATA findFileWorld;	
	HANDLE hFind = FindFirstFile((directory + L"\\*.txt").c_str(), &findFileWorld);	

	if (hFind != INVALID_HANDLE_VALUE) {
		do {
			std::wstring filePath = directory + L"\\" + findFileWorld.cFileName;	

			std::wifstream file(filePath);	
			if (file.is_open()) {
				std::wstring line;
				while (std::getline(file, line)) {
					std::wistringstream iss(line);
					std::wstring word;
					while (iss >> word) {
						if (std::find(wordArray.begin(), wordArray.end(), word) != wordArray.end()) {
							FileName inform;	
							inform.word = word;
							inform.name = findFileWorld.cFileName;	

							std::wstring wordAndNameFile = inform.word + L" //" + inform.name + L"";		

							SendMessage(hList2, LB_ADDSTRING, 0, (LPARAM)wordAndNameFile.c_str());	
							std::wstring ForbiddenWordsFilePath = L"C:\\Users\\alecs\\source\\repos\\Project20\\Project20\\Forbidden words\\" + inform.name;	
							CopyFile(filePath.c_str(), ForbiddenWordsFilePath.c_str(), FALSE);


						}
					}
				}
				file.close();	
			}
		} while (FindNextFile(hFind, &findFileWorld) != 0);		
		FindClose(hFind);	
	}
}

void RewritingWordsIntoAsterisks(const std::wstring& directory) {	
	WIN32_FIND_DATA findFileWorld;
	
}

DWORD WINAPI Thread(LPVOID lp) {
	SearchingWrongWords* p = (SearchingWrongWords*)lp;
	SearchWords(L"C:\\Users\\alecs\\source\\repos\\Project20\\Project20", p->hList2);			

	EnableWindow(p->hButton4, TRUE);	
	return 0;
}	

DWORD WINAPI Thread2(LPVOID lp) {	
	SearchingWrongWords* p = (SearchingWrongWords*)lp;
	RewritingWordsIntoAsterisks(L"C:\\Users\\alecs\\source\\repos\\Project20\\Project20\\stars instead of words");

	EnableWindow(p->hButton4, TRUE);
	return 0;
}

void SearchingWrongWords::Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
	if (id == IDC_BUTTON5) {	
		int SizeText = GetWindowTextLength(hEdit1);	

		TCHAR buffer[256];	
		GetWindowText(hEdit1, buffer, sizeof(buffer));			
		if (wcscmp(buffer, L"") != 0) {
			bool isValid = true;
			for (int i = 0; buffer[i] != '\0'; ++i) {
				if (buffer[i] == ' ') {	
					isValid = false;	
					break;
				}
			}
			if (isValid) {	
				SendMessage(hList1, LB_ADDSTRING, 0, (LPARAM)buffer);	

				TCHAR* newWord = new TCHAR[lstrlen(buffer) + 1];	
				lstrcpy(newWord, buffer);	
				wordArray.push_back(newWord);	

				SetWindowText(hEdit1, L"");	
			}
			else {
				MessageBox(NULL, L"Введено более одного слова или содержится пробел!", L"Сообщение", MB_OK | MB_ICONINFORMATION);	
			}
		}
		else {
			MessageBox(NULL, L"Невозможно добавить пустую строку!", L"Сообщение", MB_OK | MB_ICONINFORMATION);	
		}
	
	}
	if (id == IDC_BUTTON4) {	
		HANDLE h; 
		h = CreateThread(NULL, 0, Thread, this, 0, NULL);		
		CloseHandle(h);
		h = CreateThread(NULL, 0, Thread2, this, 0, NULL);		
		CloseHandle(h);	
		EnableWindow(hButton4, FALSE);				
	}
}
//"C:\Users\alecs\source\repos\Project20\Project20\stars instead of words"	
//void SearchingWrongWords::Cls_OnSize(HWND hwnd, UINT state, int cx, int cy)	
//{
//
//}


//void CWaitableTimerDlg::OnTrayIcon(WPARAM wp, LPARAM lp)
//{
//
//}

INT_PTR CALLBACK SearchingWrongWords::DlgProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)	
{
	switch (message)
	{
		HANDLE_MSG(hwnd, WM_CLOSE, ptr->Cls_OnClose);	
		HANDLE_MSG(hwnd, WM_INITDIALOG, ptr->Cls_OnInitDialog);		
		HANDLE_MSG(hwnd, WM_COMMAND, ptr->Cls_OnCommand);	
	}	
	
	/*if (message == WM_ICON)
	{
		ptr->OnTrayIcon(wParam, lParam);
		return TRUE;
	}*/
	return FALSE;
}
