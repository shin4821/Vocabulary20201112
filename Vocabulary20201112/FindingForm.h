//FindingForm.h
#ifndef _FINDINGFORM_H
#define _FINDINGFORM_H
#include<windows.h>

BOOL CALLBACK FindingFormProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
BOOL FindingForm_OnInitDialog(HWND hWnd, WPARAM wParam, LPARAM lParam);
BOOL FindingForm_OnCommand(HWND hWnd, WPARAM wParam, LPARAM lParam);
BOOL FindingForm_OnSpellingButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam);
BOOL FindingForm_OnMeaningButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam);
BOOL FindingForm_OnFindButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam);
BOOL FindingForm_OnNotify(HWND hWnd, WPARAM wParam, LPARAM lParam);
BOOL FindingForm_OnListViewItemDoubleClicked(HWND hWnd, WPARAM wParam, LPARAM lParam);
BOOL FindingForm_OnClose(HWND hWnd, WPARAM wParam, LPARAM lParam);

#endif //_FINDINGFORM_H