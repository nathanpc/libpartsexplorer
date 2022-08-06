/**
 * UIManager.cpp
 * Helps us declutter the window procedure and its associated source file.
 *
 * @author Nathan Campos <nathan@innoveworkshop.com>
 */

#include "UIManager.h"

/**
 * Constructs an empty UIManager object. Later make sure to call SetInstance and
 * SetMainWindowHandle.
 */
UIManager::UIManager() {
	this->lphInst = NULL;
	this->lphWnd = NULL;
}

/**
 * Constructs the UIManager object.
 * 
 * @param lphInst      Our application's instance.
 * @param lphwndParent The main window handle.
 */
UIManager::UIManager(HINSTANCE* lphInst, HWND* lphwndParent) {
	this->lphInst = lphInst;
	this->lphWnd = lphwndParent;
}

/**
 * Sets the application instance for us to keep track of.
 * 
 * @param lphInst Our application's instance.
 */
void UIManager::SetInstance(HINSTANCE* lphInst) {
	this->lphInst = lphInst;
}

/**
 * Sets the main window handle for us to keep track of.
 * 
 * @param lphWnd The main window handle.
 */
void UIManager::SetMainWindowHandle(HWND* lphWnd) {
	this->lphWnd = lphWnd;
}

/**
 * Opens a Pecan archive interactively via an Open File dialog.
 * 
 * @return 0 if the operation was successful.
 */
LRESULT UIManager::OpenArchiveInteractive() {
	if (!pecan.Read(_T("C:\\Users\\nathanpc\\Documents\\Visual Studio 2019\\Projects\\Pecan\\example\\example.tar"))) {
		pecan.ShowLastErrorMessage();
		return 1;
	}

	return 0;
}
