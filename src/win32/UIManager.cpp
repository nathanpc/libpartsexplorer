/**
 * UIManager.cpp
 * Helps us declutter the window procedure and its associated source file.
 *
 * @author Nathan Campos <nathan@innoveworkshop.com>
 */

#include "UIManager.h"
#include "DetailView.h"

/**
 * Constructs an empty UIManager object. Later make sure to call SetInstance and
 * SetMainWindowHandle.
 */
UIManager::UIManager() {
	this->lphInst = NULL;
	this->lphWnd = NULL;
	this->lphwndDetail = NULL;
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
 * Sets the detail window handle for us to keep track of.
 *
 * @param lphWnd The detail window handle.
 */
void UIManager::SetDetailWindowHandle(HWND* lphWnd) {
	this->lphwndDetail = lphWnd;
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

	// Populate the detail view.
	return PopulateDetailView();
}

/**
 * Populates the detail view with data from the internal Pecan archive object.
 *
 * @return 0 if the operation was successful.
 */
LRESULT UIManager::PopulateDetailView() {
	DetailViewUpdateContents(&pecan);
	return 0;
}
