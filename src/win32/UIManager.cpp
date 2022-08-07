/**
 * UIManager.cpp
 * Helps us declutter the window procedure and its associated source file.
 *
 * @author Nathan Campos <nathan@innoveworkshop.com>
 */

#include "UIManager.h"

#include <commdlg.h>
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
	OPENFILENAME ofn = { 0 };
	TCHAR szPath[MAX_PATH] = _T("");

	// Clear the screen.
	DetailViewClear();

	// Populate the open file dialog structure.
	ofn.lStructSize = sizeof(ofn);
	ofn.lpstrTitle = L"Open Pecan Archive";
	ofn.hwndOwner = *this->lphWnd;
	ofn.lpstrFilter = _T("Pecan Archive (*.tar)\0*.tar\0All Files (*.*)\0*.*\0");
	ofn.lpstrFile = szPath;
	ofn.nMaxFile = MAX_PATH;
	ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST;
	ofn.lpstrDefExt = L"tar";

	// Open the open folder dialog.
	if (!GetOpenFileName(&ofn))
		return 1;

	// Read the archive.
	if (!pecan.Read(szPath)) {
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
