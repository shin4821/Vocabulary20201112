//FindingForm.c
#include"FindingForm.h"
#include"Vocabulary.h"
#include"resource.h"
#include<stdio.h>
#include<stdlib.h>
#include<Commctrl.h>
#pragma warning(disable:4996)

BOOL CALLBACK FindingFormProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	BOOL ret;
	switch (message) {
	case WM_INITDIALOG:
		ret = FindingForm_OnInitDialog(hWnd, wParam, lParam);
		break;

	case WM_COMMAND:
		ret = FindingForm_OnCommand(hWnd, wParam, lParam);
		break;

	case WM_NOTIFY:
		ret = FindingForm_OnNotify(hWnd, wParam, lParam);
		break;

	case WM_CLOSE:
		ret = FindingForm_OnClose(hWnd, wParam, lParam);
		break;

	default:
		ret = FALSE;
		break;
	}
	return ret;
}

BOOL FindingForm_OnCommand(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	BOOL ret;
	switch (LOWORD(wParam)) {
	case IDC_BUTTON_SPELLING:
		ret = FindingForm_OnSpellingButtonClicked(hWnd, wParam, lParam);
		break;

	case IDC_BUTTON_MEANING:
		ret = FindingForm_OnMeaningButtonClicked(hWnd, wParam, lParam);
		break;

	case IDC_BUTTON_FIND:
		ret = FindingForm_OnFindButtonClicked(hWnd, wParam, lParam);
		break;

	default:
		ret = FALSE;
		break;
	}
	return ret;
}

BOOL FindingForm_OnNotify(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	BOOL ret;
	switch (wParam) {
	case IDC_LIST_WORDS:
		ret = FindingForm_OnListViewItemDoubleClicked(hWnd, wParam, lParam);
		break;

	default:
		ret = FALSE;
		break;
	}
	return TRUE;
}

BOOL FindingForm_OnInitDialog(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	LVCOLUMN column = { 0, };

	//1. ã�� �����찡 �����ɶ�
	  //1.1 ����Ʈ�� ��Ʈ���� ����� �����.
	column.mask = LVCF_WIDTH | LVCF_TEXT;
	column.cx = 50;
	column.pszText = "��ȣ";
	SendMessage(GetDlgItem(hWnd, IDC_LIST_WORDS), LVM_INSERTCOLUMN, (WPARAM)0, (LPARAM)&column);

	column.cx = 100;
	column.pszText = "ö��";
	SendMessage(GetDlgItem(hWnd, IDC_LIST_WORDS), LVM_INSERTCOLUMN, (WPARAM)1, (LPARAM)&column);

	column.pszText = "ǰ��";
	SendMessage(GetDlgItem(hWnd, IDC_LIST_WORDS), LVM_INSERTCOLUMN, (WPARAM)2, (LPARAM)&column);

	column.cx = 80;
	column.pszText = "�ǹ�";
	SendMessage(GetDlgItem(hWnd, IDC_LIST_WORDS), LVM_INSERTCOLUMN, (WPARAM)3, (LPARAM)&column);

	column.cx = 150;
	column.pszText = "����";
	SendMessage(GetDlgItem(hWnd, IDC_LIST_WORDS), LVM_INSERTCOLUMN, (WPARAM)4, (LPARAM)&column);

	SendMessage(GetDlgItem(hWnd, IDC_LIST_WORDS),
		LVM_SETEXTENDEDLISTVIEWSTYLE,
		LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES,
		LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	SendMessage(GetDlgItem(hWnd, IDC_BUTTON_SPELLING), BM_SETCHECK, (WPARAM)BST_CHECKED, 0);

		return TRUE;

}

BOOL FindingForm_OnSpellingButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	//2. ö�� ��ư�� Ŭ������ ��
	if (HIWORD(wParam) == BN_CLICKED) {
		//2.1 �ǹ̸� �����.
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_MEANING), WM_SETTEXT, 0, (LPARAM)(LPCTSTR)"");
	}
	return TRUE;
}

BOOL FindingForm_OnMeaningButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	//3. �ǹ� ��ư�� Ŭ������ ��
	if (HIWORD(wParam) == BN_CLICKED) {
		//2.1 �ǹ̸� �����.
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_SPELLING), WM_SETTEXT, 0, (LPARAM)(LPCTSTR)"");
	}
	return TRUE;
}

BOOL FindingForm_OnFindButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	Vocabulary* vocabulary;
	int spellingButtonStatus;
	int meaningButtonStatus;
	TCHAR spelling[32];
	TCHAR meaning[32];
	Long(*indexes);
	Long count;
	TCHAR number[64];
	LVITEM item = { 0, };
	HWND vocabularyForm;
	int i;
	Word word;

	//4. ã�� ��ư�� Ŭ��������
	if (HIWORD(wParam) == BN_CLICKED) {
		//4.1 ö�� ��ư�� �д´�.
		spellingButtonStatus = SendMessage(GetDlgItem(hWnd, IDC_BUTTON_SPELLING), BM_GETCHECK, 0, 0);

		//4.2 ö�ڸ� �д´�.
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_SPELLING), WM_GETTEXT, (WPARAM)32, (LPARAM)spelling);

		//4.3 �ǹ� ��ư�� �д´�.
		meaningButtonStatus = SendMessage(GetDlgItem(hWnd, IDC_BUTTON_MEANING), BM_GETCHECK, 0, 0);

		//4.4 �ǹ̸� �д´�.
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_MEANING), WM_GETTEXT, (WPARAM)32, (LPARAM)meaning);

		//4.5 �ܾ��� �����츦 ã�´�.
		vocabularyForm = FindWindow("#32770", "�ܾ���");
		
		//4.6 �ܾ��� �������� �ܾ��忡�� ���ǿ� ���� ã�´�.
		vocabulary = (Vocabulary*)GetWindowLong(vocabularyForm, GWL_USERDATA);
		indexes = (Long(*))GetWindowLong(hWnd, GWL_USERDATA);
		if (indexes != NULL) {
			free(indexes);
			indexes = NULL;
		}
		if (spellingButtonStatus == BST_CHECKED) {
			FindBySpelling(vocabulary, spelling, &indexes, &count);
		}
		else if (meaningButtonStatus == BST_CHECKED) {
			FindByMeaning(vocabulary, meaning, &indexes, &count);
		}
		SetWindowLong(hWnd, GWL_USERDATA, (LONG)indexes);

		//4.7 ����Ʈ����Ʈ���� ��� �׸��� �����.
		SendMessage(GetDlgItem(hWnd, IDC_LIST_WORDS), LVM_DELETEALLITEMS, 0, 0);

		//4.8 �ܾ����� count��ŭ ����Ʈ�� ��Ʈ�ѿ� �׸��� �߰��Ѵ�.
		item.mask = LVIF_TEXT;
		i = 0;
		while (i < count) {
			
			item.iItem = i;
			item.iSubItem = 0;
			sprintf(number, "%d", i + 1);
			item.pszText = number;
			SendMessage(GetDlgItem(hWnd, IDC_LIST_WORDS), LVM_INSERTITEM, 0, (LPARAM)&item);

			word = Vocabulary_GetAt(vocabulary, indexes[i]);
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

BOOL FindingForm_OnListViewItemDoubleClicked(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	int index;
	LVITEM item = { 0, };
	Long(*indexes);
	TCHAR spelling[32];
	TCHAR meaning[32];
	TCHAR wordClass[12];
	TCHAR example[64];
	HWND vocabularyForm;

	//5. ����Ʈ����Ʈ���� �������� ����Ŭ�� ������
	if (((LPNMHDR)lParam)->code == NM_DBLCLK) {
		//5.1 ����Ʈ����Ʈ���� ��ȣ�� �д´�.
		index = SendMessage(GetDlgItem(hWnd, IDC_LIST_WORDS), LVM_GETSELECTIONMARK, 0, 0);
		//5.2 ö��, ���, �ǹ�, ���ø� �д´�.
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

		//5.3 �ܾ��� �����츦 ã�´�.
		vocabularyForm = FindWindow("#32770", "�ܾ���");

		//5.4 �ܾ��� �������� �ܾ ö��, ǰ��, �ǹ�, ���ø� ���´�.
		SendMessage(GetDlgItem(vocabularyForm, IDC_EDIT_SPELLING), WM_SETTEXT, 0, (LPARAM)(LPCTSTR)spelling);
		SendMessage(GetDlgItem(vocabularyForm, IDC_EDIT_WORDCLASSES), WM_SETTEXT, 0, (LPARAM)(LPCTSTR)wordClass);
		SendMessage(GetDlgItem(vocabularyForm, IDC_EDIT_MEANING), WM_SETTEXT, 0, (LPARAM)(LPCTSTR)meaning);
		SendMessage(GetDlgItem(vocabularyForm, IDC_EDIT_EXAMPLE), WM_SETTEXT, 0, (LPARAM)(LPCTSTR)example);

		//5.5 �ܾ��� �������� ����Ʈ����Ʈ�ѿ� �ش� �׸��� �����Ѵ�.
		indexes = (Long(*))GetWindowLong(hWnd, GWL_USERDATA);
		SendMessage(GetDlgItem(vocabularyForm, IDC_LIST_WORDS), LVM_SETSELECTIONMARK, 0, (LPARAM)indexes[index]);
		if (indexes != NULL) {
			free(indexes);
			indexes = NULL;
		}

		//5.6 ã�� �����츦 �����Ѵ�.
		EndDialog(hWnd, 0);
	}
	return TRUE;
}

BOOL FindingForm_OnClose(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	Long(*indexes);
	
	//6. �ݱ� ��ư�� Ŭ������ ��
	  //6.1 ã�� �����츦 �����Ѵ�.
	  indexes = (Long(*))GetWindowLong(hWnd, GWL_USERDATA);
	  if (indexes != NULL) {
		  free(indexes);
		  indexes = NULL;
	  }
	  EndDialog(hWnd, 0);
}