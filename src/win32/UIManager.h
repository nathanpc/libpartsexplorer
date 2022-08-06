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
	HWND* lphwndDetail;
	Pecan pecan;

public:
	// Constructors and Destructors
	UIManager();

	// Important Bits Setters
	void SetInstance(HINSTANCE* lphInst);
	void SetMainWindowHandle(HWND* lphWnd);
	void SetDetailWindowHandle(HWND* lphWnd);

	// Common Operations.
	LRESULT OpenArchiveInteractive();

protected:
	LRESULT PopulateDetailView();
};
