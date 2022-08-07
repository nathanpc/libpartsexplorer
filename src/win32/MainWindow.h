/**
 * WinPecan
 * Windows application to help you deal with your Pecan archives.
 * 
 * @author Nathan Campos <nathan@innoveworkshop.com>
 */

#pragma once

#include "stdafx.h"
#include "UIManager.h"

// Global variables.
HINSTANCE g_hInst;
HWND g_hWnd;
HWND* g_lphwndDetailView;
UIManager uiManager;

// Initialization
ATOM RegisterWndClass();
BOOL PopulateWindow();
BOOL InitInstance(int nCmdShow);

// Main window's event handlers.
LRESULT WndMainClose(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
LRESULT WndMainDestroy(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

// Menu event handlers.
LRESULT MenuOpenArchive(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
