//VocabularyForm.h
#ifndef _VOCABULARYFORM_H
#define _VOCABULARYFORM_H
#include<windows.h>

BOOL CALLBACK VocabularyFormProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
BOOL VocabularyForm_OnInitDialog(HWND hWnd, WPARAM wParam, LPARAM lParam);
BOOL VocabularyForm_OnCommand(HWND hWnd, WPARAM wParam, LPARAM lParam);
BOOL VocabularyForm_OnRecordButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam);
BOOL VocabularyForm_OnFindButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam);
BOOL VocabularyForm_OnCorrectButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam);
BOOL VocabularyForm_OnEraseButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam);
BOOL VocabularyForm_OnArrangeButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam);
BOOL VocabularyForm_OnListViewItemDoubleClicked(HWND hWnd, WPARAM wParam, LPARAM lParam);
BOOL VocabularyForm_OnClose(HWND hWnd, WPARAM wParam, LPARAM lParam);

#endif //_VOCABULARYFORM_H