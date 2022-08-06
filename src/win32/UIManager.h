/**
 * UIManager.h
 * Helps us declutter the window procedure and its associated source file.
 * 
 * @author Nathan Campos <nathan@innoveworkshop.com>
 */

#pragma once

#include "stdafx.h"
#include "WinPecan.h"

class UIManager {
protected:
	HINSTANCE* lphInst;
	HWND* lphWnd;
	Pecan pecan;

public:
	// Constructors and Destructors
	UIManager();
	UIManager(HINSTANCE* hInst, HWND* hwndParent);

	// Important Bits Setters
	void SetInstance(HINSTANCE* hInst);
	void SetMainWindowHandle(HWND* hWnd);

	// Common Operations.
	LRESULT OpenArchiveInteractive();
};
