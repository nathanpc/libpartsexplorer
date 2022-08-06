/**
 * DetailView.cpp
 * Handles the creation and the events of the detail view "dialog".
 *
 * @author Nathan Campos <nathan@innoveworkshop.com>
 */

#include "DetailView.h"

// Instance Variables
HWND hwndDetail;
HWND* lphwndParent;

// Private methods.
INT_PTR DlgDetailResize(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);
INT_PTR CALLBACK DetailDlgProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);

/**
 * Creates the detail view in its appropriate place.
 * 
 * @param hInst  Application's instance.
 * @param lphWnd Parent window to place the view into.
 * @param rect   Position and size of the detail view in the parent window.
 */
void CreateDetailView(HINSTANCE hInst, HWND* lphWnd, RECT rect) {
	lphwndParent = lphWnd;

	// Load some needed resources.
	HRSRC hResDialog = FindResource(hInst, MAKEINTRESOURCE(IDD_DETAILVIEW), RT_DIALOG);
	HGLOBAL hgDialog = LoadResource(hInst, hResDialog);

	// Embed the detail view dialog into the window.
	hwndDetail = CreateDialogIndirectParam(hInst, (LPCDLGTEMPLATE)hgDialog,
		*lphWnd, DetailDlgProc, (LPARAM)&rect);
	SetWindowPos(hwndDetail, HWND_TOP, rect.left, rect.top, rect.right, rect.bottom,
		SWP_SHOWWINDOW);
}

/**
 * Destroys the dialog instance.
 * 
 * @return TRUE if everything was fine.
 */
INT_PTR DestroyDetailView() {
	EndDialog(hwndDetail, IDOK);
	return (INT_PTR)TRUE;
}

/**
 * WM_SIZE event being forwarded from the parent window.
 * 
 * @param  hWnd   Parent window handle.
 * @param  uMsg   WM_SIZE message ID.
 * @param  wParam The type of resizing requested.
 * @param  lParam The LOWORD specifies the new width and HIWORD the new height.
 * 
 * @return        1 if we have handled the event.
 */
LRESULT ResizeDetailView(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	// Get the dialog position and size.
	RECT rcDialog;
	GetWindowRect(hwndDetail, &rcDialog);

	// Calculate the new size and position.
	rcDialog.top = 0;
	rcDialog.left = DEFAULT_UI_MARGIN;
	rcDialog.right = LOWORD(lParam) - rcDialog.left - DEFAULT_UI_MARGIN;
	rcDialog.bottom = HIWORD(lParam) - rcDialog.top - DEFAULT_UI_MARGIN;

	// Resize the dialog.
	return (LRESULT)SetWindowPos(hwndDetail, HWND_TOP, rcDialog.left, rcDialog.top,
		rcDialog.right, rcDialog.bottom, SWP_SHOWWINDOW);
}

/**
 * Message handler for the detail dialog.
 *
 * @param  hDlg   A handle to the dialog.
 * @param  uMsg   The message.
 * @param  wParam Additional message-specific information.
 * @param  lParam Additional message-specific information.
 * @return        TRUE if we processed the message, and FALSE if we didn't.
 */
INT_PTR CALLBACK DetailDlgProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	int wmId, wmEvent;

	switch (uMsg) {
	case WM_INITDIALOG:
		// Dialog has just been initialized.
		return (INT_PTR)TRUE;
	case WM_COMMAND:
		// Someone is trying to interact with us.
		wmId = LOWORD(wParam);
		wmEvent = HIWORD(wParam);

		switch (wmId) {
		case IDOK:
		case IDCANCEL:
			// Time to close the dialog up.
			return DestroyDetailView();
		}
		break;
	case WM_SIZE:
		return DlgDetailResize(hDlg, uMsg, wParam, lParam);
	}

	// Nothing happened.
	return (INT_PTR)FALSE;
}

/**
 * Handles the WM_SIZE event.
 */
INT_PTR DlgDetailResize(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	// Get the dialog position and size.
	RECT rcDialog;
	GetWindowRect(hDlg, &rcDialog);

	// Get the image static position and size.
	RECT rcImage;
	GetWindowRect(GetDlgItem(hDlg, IDC_IMAGE), &rcImage);

	// Calculate the package combo box size and position.
	HWND hwndPackage = GetDlgItem(hDlg, IDC_COMBO_PACKAGE);
	RECT rcPackage;
	GetWindowRect(hwndPackage, &rcPackage);
	rcPackage.bottom = rcDialog.bottom - rcDialog.top - rcPackage.top;
	rcPackage.left -= rcDialog.left;
	rcPackage.top -= rcDialog.top;
	rcPackage.right = rcDialog.right - rcDialog.left - rcPackage.left;

	// Calculate the description edit size and position.
	HWND hwndDesc = GetDlgItem(hDlg, IDC_EDIT_DESCRIPTION);
	RECT rcDesc;
	GetWindowRect(hwndDesc, &rcDesc);
	rcDesc.bottom = rcDesc.bottom - rcDesc.top;
	rcDesc.left -= rcDialog.left;
	rcDesc.top -= rcDialog.top;
	rcDesc.right = rcDialog.right - rcDialog.left - rcDesc.left;

	// Calculate the attributes table size and position.
	HWND hwndAttrib = GetDlgItem(hDlg, IDC_LIST_ATTRS);
	RECT rcAttrib;
	GetWindowRect(hwndAttrib, &rcAttrib);
	rcAttrib.bottom = rcDialog.bottom - rcAttrib.top;
	rcAttrib.left -= rcDialog.left;
	rcAttrib.top -= rcDialog.top;
	rcAttrib.right = rcDialog.right - rcDialog.left - rcAttrib.left;

	// Expand the dynamic controls in the view.
	SetWindowPos(hwndPackage, HWND_TOP, rcPackage.left, rcPackage.top, rcPackage.right,
		rcPackage.bottom, SWP_SHOWWINDOW);
	SetWindowPos(hwndDesc, HWND_TOP, rcDesc.left, rcDesc.top, rcDesc.right, rcDesc.bottom,
		SWP_SHOWWINDOW);
	SetWindowPos(hwndAttrib, HWND_TOP, rcAttrib.left, rcAttrib.top, rcAttrib.right,
		rcAttrib.bottom, SWP_SHOWWINDOW);

	return (INT_PTR)TRUE;
}
