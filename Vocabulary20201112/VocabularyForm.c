//VocabularyForm.c
#include"VocabularyForm.h"
#include"Vocabulary.h"
#include"resource.h"
#include"FindingForm.h"
#include<stdio.h>
#include<stdlib.h>
#include<Commctrl.h>
#pragma warning(disable:4996)


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	int response;
	response = DialogBox(hInstance, MAKEINTRESOURCE(IDD_VOCABULARYFORM), NULL, VocabularyFormProc);
	return response;
}

BOOL CALLBACK VocabularyFormProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	BOOL ret;

	switch (message) {
	case WM_INITDIALOG:
		ret = VocabularyForm_OnInitDialog(hWnd, wParam, lParam);
		break;

	case WM_COMMAND:
		ret = VocabularyForm_OnCommand(hWnd, wParam, lParam);
		break;

	case WM_NOTIFY:
		ret = VocabularyForm_OnNotify(hWnd, wParam, lParam);
		break;

	case WM_CLOSE:
		ret = VocabularyForm_OnClose(hWnd, wParam, lParam);
		break;

	default:
		ret = FALSE;
		break;
	}
	return ret;
}

BOOL VocabularyForm_OnCommand(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	BOOL ret;
	switch (LOWORD(wParam)) {
	case IDC_BUTTON_RECORD:
		ret = VocabularyForm_OnRecordButtonClicked(hWnd, wParam, lParam);
		break;

	case IDC_BUTTON_FIND:
		ret = VocabularyForm_OnFindButtonClicked(hWnd, wParam, lParam);
		break;

	case IDC_BUTTON_CORRECT:
		ret = VocabularyForm_OnCorrectButtonClicked(hWnd, wParam, lParam);
		break;

	case IDC_BUTTON_ERASE:
		ret = VocabularyForm_OnEraseButtonClicked(hWnd, wParam, lParam);
		break;

	case IDC_BUTTON_ARRANGE:
		ret = VocabularyForm_OnArrangeButtonClicked(hWnd, wParam, lParam);
		break;

	default:
		ret = FALSE;
		break;
	}
	return ret;
}

BOOL VocabularyForm_OnNotify(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	BOOL ret;
	switch(wParam) {
	case IDC_LIST_WORDS:
		ret = VocabularyForm_OnListViewItemDoubleClicked(hWnd, wParam, lParam);
		break;

	default:
		ret = FALSE;
		break;
	}
	return ret;
}


BOOL VocabularyForm_OnInitDialog(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	Vocabulary* vocabulary;
	LVCOLUMN column = { 0, };
	int i = 0;
	LVITEM item = { 0, };
	TCHAR wordClasses[][8] = {"명사","대명사","동사","부사","형용사","전치사","접속사","감탄사"};
	TCHAR number[64];
	Word word;

	//1. 윈도우가 생성될 때
	  //1.1 단어장을 만든다.
	  vocabulary = (Vocabulary*)malloc(sizeof(Vocabulary));
	  Vocabulary_Create(vocabulary, 10000);
	  SetWindowLong(hWnd, GWL_USERDATA, (LONG)vocabulary);

	  //1.2 적재한다.
	  Load(vocabulary);

	  //1.3 리스트뷰 컨트롤의 헤더를 만든다.
	  column.mask = LVCF_WIDTH | LVCF_TEXT;
	  column.cx = 50;
	  column.pszText = "번호";
	  SendMessage(GetDlgItem(hWnd, IDC_LIST_WORDS), LVM_INSERTCOLUMN, (WPARAM)0, (LPARAM)&column);

	  column.cx = 100;
	  column.pszText = "철자";
	  SendMessage(GetDlgItem(hWnd, IDC_LIST_WORDS), LVM_INSERTCOLUMN, (WPARAM)1, (LPARAM)&column);

	  column.cx = 80;
	  column.pszText = "품사";
	  SendMessage(GetDlgItem(hWnd, IDC_LIST_WORDS), LVM_INSERTCOLUMN, (WPARAM)2, (LPARAM)&column);

	  column.cx = 150;
	  column.pszText = "의미";
	  SendMessage(GetDlgItem(hWnd, IDC_LIST_WORDS), LVM_INSERTCOLUMN, (WPARAM)3, (LPARAM)&column);

	  column.cx = 200;
	  column.pszText = "예시";
	  SendMessage(GetDlgItem(hWnd, IDC_LIST_WORDS), LVM_INSERTCOLUMN, (WPARAM)4, (LPARAM)&column);

	  SendMessage(GetDlgItem(hWnd, IDC_LIST_WORDS),
		  LVM_SETEXTENDEDLISTVIEWSTYLE,
		  LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES,
		  LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	  //1.4 적재된 개수만큼 리스트뷰 컨트롤에 항목을 추가한다.
	  item.mask = LVIF_TEXT;
	  i = 0;
	  while (i < vocabulary->length) {
		  word = Vocabulary_GetAt(vocabulary, i);
		  item.iItem = i;
		  item.iSubItem = 0;
		  sprintf(number, "%d", i + 1);
		  item.pszText = number;
		  SendMessage(GetDlgItem(hWnd, IDC_LIST_WORDS), LVM_INSERTITEM, 0, (LPARAM)&item);

		  item.iSubItem = 1;
		  item.pszText = word.spelling;
		  SendMessage(GetDlgItem(hWnd, IDC_LIST_WORDS), LVM_SETITEMTEXT, (WPARAM)i, (LPARAM)&item);

		  item.iSubItem = 2;
		  item.pszText = word.wordClass;
		  SendMessage(GetDlgItem(hWnd, IDC_LIST_WORDS), LVM_SETITEMTEXT, (WPARAM)i, (LPARAM)&item);

		  item.iSubItem = 3;
		  item.pszText = word.meaning;
		  SendMessage(GetDlgItem(hWnd, IDC_LIST_WORDS), LVM_SETITEMTEXT, (WPARAM)i, (LPARAM)&item);

		  item.iSubItem = 4;
		  item.pszText = word.example;
		  SendMessage(GetDlgItem(hWnd, IDC_LIST_WORDS), LVM_SETITEMTEXT, (WPARAM)i, (LPARAM)&item);
		  
		  i++;
	  }
	  //1.5 콤보박스 목록에 품사 항목을 추가한다.
	  for (i = 0; i < sizeof(wordClasses) / sizeof(wordClasses[0]); i++) {
		  SendMessage(GetDlgItem(hWnd, IDC_EDIT_WORDCLASSES), CB_ADDSTRING, 0, (LPARAM)(LPCTSTR)wordClasses[i]);

	  }
	  return TRUE;
}

BOOL VocabularyForm_OnFindButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	//3. 찾기 버튼을 클릭했을 때
	if (HIWORD(wParam) == BN_CLICKED) {
		//3.1 찾기 윈도우를 출력한다.
		DialogBox((HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE), MAKEINTRESOURCE(IDD_FINDINGFORM), hWnd,
			FindingFormProc);
	}
	return TRUE;
}

BOOL VocabularyForm_OnRecordButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	TCHAR spelling[32];
	TCHAR wordClass[12];
	TCHAR meaning[32];
	TCHAR example[64];
	int index;
	Vocabulary* vocabulary;
	LVITEM item = { 0, };
	TCHAR number[64];
	Word word;

	//2. 기재하기 버튼을 클릭했을 때
	if (HIWORD(wParam) == BN_CLICKED) {
		//2.1 철자, 품사, 의미, 예시를 읽는다.
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_SPELLING), WM_GETTEXT, (WPARAM)32, (LPARAM)spelling);
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_WORDCLASSES), WM_GETTEXT, (WPARAM)12, (LPARAM)wordClass);
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_MEANING), WM_GETTEXT, (WPARAM)32, (LPARAM)meaning);
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_EXAMPLE), WM_GETTEXT, (WPARAM)64, (LPARAM)example);

		//2.2 단어장에 기재한다.
		vocabulary = (Vocabulary*)GetWindowLong(hWnd, GWL_USERDATA);
		index = Record(vocabulary, spelling, wordClass, meaning, example);
		word = Vocabulary_GetAt(vocabulary, index);

		//2.3 리스트뷰컨트롤에 해당 항목을 추가한다.
		item.mask = LVIF_TEXT;
		item.iItem = index;
		item.iSubItem = 0;
		sprintf(number, "%d", index + 1);
		item.pszText = number;
		SendMessage(GetDlgItem(hWnd, IDC_LIST_WORDS), LVM_INSERTITEM, 0, (LPARAM)&item);

		item.iSubItem = 1;
		item.pszText = word.spelling;
		SendMessage(GetDlgItem(hWnd, IDC_LIST_WORDS), LVM_SETITEMTEXT, (WPARAM)index, (LPARAM)&item);

		item.iSubItem = 2;
		item.pszText = word.wordClass;
		SendMessage(GetDlgItem(hWnd, IDC_LIST_WORDS), LVM_SETITEMTEXT, (WPARAM)index, (LPARAM)&item);

		item.iSubItem = 3;
		item.pszText = word.meaning;
		SendMessage(GetDlgItem(hWnd, IDC_LIST_WORDS), LVM_SETITEMTEXT, (WPARAM)index, (LPARAM)&item);

		item.iSubItem = 4;
		item.pszText = word.example;
		SendMessage(GetDlgItem(hWnd, IDC_LIST_WORDS), LVM_SETITEMTEXT, (WPARAM)index, (LPARAM)&item);
	}
	return TRUE;
}

BOOL VocabularyForm_OnCorrectButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	TCHAR wordClass[12];
	TCHAR meaning[32];
	TCHAR example[64];
	int index;
	LVITEM item = { 0, };
	Vocabulary* vocabulary;
	Word word;

	//4. 고치기 버튼을 클릭했을 때
	if (HIWORD(wParam) == BN_CLICKED) {
		//4.1 품사, 의미, 예시를 읽는다.
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_WORDCLASSES), WM_GETTEXT, (WPARAM)8, (LPARAM)wordClass);
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_MEANING), WM_GETTEXT, (WPARAM)32, (LPARAM)meaning);
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_EXAMPLE), WM_GETTEXT, (WPARAM)64, (LPARAM)example);

		//4.2 리스트뷰컨트롤의 번호를 읽는다.
		index = SendMessage(GetDlgItem(hWnd, IDC_LIST_WORDS), LVM_GETSELECTIONMARK, 0, 0);
		
		//4.3 단어장에서 고친다.
		vocabulary = (Vocabulary*)GetWindowLong(hWnd, GWL_USERDATA);
		index = Correct(vocabulary, index, wordClass, meaning, example);
		word = Vocabulary_GetAt(vocabulary, index);

		//4.4 리스트뷰컨트롤에서 해당 항목을 고친다.
		item.mask = LVIF_TEXT;
		item.iSubItem = 1;
		item.pszText = word.spelling;
		SendMessage(GetDlgItem(hWnd, IDC_LIST_WORDS), LVM_SETITEMTEXT, (WPARAM)index, (LPARAM)&item);

		item.iSubItem = 2;
		item.pszText = word.wordClass;
		SendMessage(GetDlgItem(hWnd, IDC_LIST_WORDS), LVM_SETITEMTEXT, (WPARAM)index, (LPARAM)&item);

		item.iSubItem = 3;
		item.pszText = word.meaning;
		SendMessage(GetDlgItem(hWnd, IDC_LIST_WORDS), LVM_SETITEMTEXT, (WPARAM)index, (LPARAM)&item);

		item.iSubItem = 4;
		item.pszText = word.example;
		SendMessage(GetDlgItem(hWnd, IDC_LIST_WORDS), LVM_SETITEMTEXT, (WPARAM)index, (LPARAM)&item);
	}
	return TRUE;
}

BOOL VocabularyForm_OnEraseButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	int index;
	Vocabulary* vocabulary;
	LVITEM item = { 0, };
	TCHAR number[64];

	//5. 지우기 버튼을 클릭했을 때
	if (HIWORD(wParam) == BN_CLICKED) {
		//5.1 리스트뷰 컨트롤의 번호를 읽는다.
		index = SendMessage(GetDlgItem(hWnd, IDC_LIST_WORDS), LVM_GETSELECTIONMARK, 0, 0);

		//5.2 단어장에서 지운다.
		vocabulary = (Vocabulary*)GetWindowLong(hWnd, GWL_USERDATA);
		Erase(vocabulary, index);

		//5.3 리스트뷰 컨트롤에서 해당 항목을 지운다.
		SendMessage(GetDlgItem(hWnd, IDC_LIST_WORDS), LVM_DELETEITEM, (WPARAM)index, 0);

		//5.4 지워진 항목 번호의 하위 번호들에 대하여, 1씩 뺀다.
		item.mask = LVIF_TEXT;
		while (index < vocabulary->length) {
			item.iSubItem = 0;
			sprintf(number, "%d", index + 1);
			item.pszText = number;
			SendMessage(GetDlgItem(hWnd, IDC_LIST_WORDS), LVM_SETITEMTEXT, (WPARAM)index, (LPARAM)&item);
			index++;
		}
	}
	return TRUE;
}

BOOL VocabularyForm_OnArrangeButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	Vocabulary* vocabulary;
	TCHAR number[64];
	int i = 0;
	LVITEM item = { 0, };
	Word word;

	//6. 정리하기 버튼을 클릭했을 때
	if (HIWORD(wParam) == BN_CLICKED) {
		//6.1 단어장에서 정리한다.
		vocabulary = (Vocabulary*)GetWindowLong(hWnd, GWL_USERDATA);
		Arrange(vocabulary);

		//6.2 리스트뷰컨트롤에서 전체 항목을 지운다.
		SendMessage(GetDlgItem(hWnd, IDC_LIST_WORDS), LVM_DELETEALLITEMS, 0, 0);

		//6.3 단어장의 length만큼 리스트뷰 컨트롤에 항목들을 추가한다.
		item.mask = LVIF_TEXT;
		while (i < vocabulary->length) {
			
			item.iItem = i;
			item.iSubItem = 0;
			sprintf(number, "%d", i + 1);
			item.pszText = number;
			SendMessage(GetDlgItem(hWnd, IDC_LIST_WORDS), LVM_INSERTITEM, 0, (LPARAM)&item);

			word = Vocabulary_GetAt(vocabulary, i);
			item.iSubItem = 1;
			item.pszText = word.spelling;
			SendMessage(GetDlgItem(hWnd, IDC_LIST_WORDS), LVM_SETITEMTEXT, (WPARAM)i, (LPARAM)&item);

			item.iSubItem = 2;
			item.pszText = word.wordClass;
			SendMessage(GetDlgItem(hWnd, IDC_LIST_WORDS), LVM_SETITEMTEXT, (WPARAM)i, (LPARAM)&item);

			item.iSubItem = 3;
			item.pszText = word.meaning;
			SendMessage(GetDlgItem(hWnd, IDC_LIST_WORDS), LVM_SETITEMTEXT, (WPARAM)i, (LPARAM)&item);

			item.iSubItem = 4;
			item.pszText = word.example;
			SendMessage(GetDlgItem(hWnd, IDC_LIST_WORDS), LVM_SETITEMTEXT, (WPARAM)i, (LPARAM)&item);

			i++;
		}
	}
	return TRUE;
}

BOOL VocabularyForm_OnListViewItemDoubleClicked(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	LVITEM item = { 0, };
	TCHAR spelling[32];
	TCHAR wordClass[12];
	TCHAR meaning[32];
	TCHAR example[64];
	int index;

	//7. 리스트뷰 컨트롤의 아이템을 더블 클릭 했을 때
	if (((LPNMHDR)lParam)->code == NM_DBLCLK) {
		//7.1 리스트뷰 컨트롤의 항목 번호를 읽는다.
		index = SendMessage(GetDlgItem(hWnd, IDC_LIST_WORDS), LVM_GETSELECTIONMARK, 0, 0);

		//7.2 철자, 품사, 의미, 예시를 읽는다.
		item.mask = LVIF_TEXT;
		item.iItem = index;
		item.iSubItem = 1;
		item.pszText = spelling;
		item.cchTextMax = 32;
		SendMessage(GetDlgItem(hWnd, IDC_LIST_WORDS), LVM_GETITEMTEXT, (WPARAM)index, (LPARAM)&item);

		item.iSubItem = 2;
		item.pszText = wordClass;
		item.cchTextMax = 12;
		SendMessage(GetDlgItem(hWnd, IDC_LIST_WORDS), LVM_GETITEMTEXT, (WPARAM)index, (LPARAM)&item);

		item.iSubItem = 3;
		item.pszText = meaning;
		item.cchTextMax = 32;
		SendMessage(GetDlgItem(hWnd, IDC_LIST_WORDS), LVM_GETITEMTEXT, (WPARAM)index, (LPARAM)&item);

		item.iSubItem = 4;
		item.pszText = example;
		item.cchTextMax = 64;
		SendMessage(GetDlgItem(hWnd, IDC_LIST_WORDS), LVM_GETITEMTEXT, (WPARAM)index, (LPARAM)&item);

		//7.3 단어에 철자, 품사, 의미, 예시를 적는다.
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_SPELLING), WM_SETTEXT, 0, (LPARAM)(LPCTSTR)spelling);
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_WORDCLASSES), WM_SETTEXT, 0, (LPARAM)(LPCTSTR)wordClass);
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_MEANING), WM_SETTEXT, 0, (LPARAM)(LPCTSTR)meaning);
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_EXAMPLE), WM_SETTEXT, 0, (LPARAM)(LPCTSTR)example);
	}
	return TRUE;
}

BOOL VocabularyForm_OnClose(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	Vocabulary* vocabulary;

	//8. 닫기 버튼을 클릭했을 때
	vocabulary = (Vocabulary*)GetWindowLong(hWnd, GWL_USERDATA);
	if (vocabulary != NULL) {
		//8.1 저장한다.
		Save(vocabulary);

		//8.2 단어장을 없앤다.
		Vocabulary_Destroy(vocabulary);
		free(vocabulary);
		vocabulary = NULL;
	}
	//8.3 윈도우를 종료한다.
	EndDialog(hWnd, 0);

	return TRUE;
}
