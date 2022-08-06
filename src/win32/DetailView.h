/**
 * DetailView.h
 * Handles the creation and the events of the detail view "dialog".
 * 
 * @author Nathan Campos <nathan@innoveworkshop.com>
 */

#pragma once

#include "stdafx.h"

// Initialization and Destruction
void CreateDetailView(HINSTANCE hInst, HWND* lphwndParent, RECT rect);
INT_PTR DestroyDetailView();

// Event Forwarding
LRESULT ResizeDetailView(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
