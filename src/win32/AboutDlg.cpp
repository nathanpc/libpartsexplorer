/**
 * AboutDlg.cpp
 * A simple about dialog.
 *
 * @author Nathan Campos <nathan@innoveworkshop.com>
 */

#include "AboutDlg.h"

// Private methods.
INT_PTR CALLBACK AboutDlgProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam);

/**
 * Shows the about dialog box.
 * 
 * @param hInst      Application's instance.
 * @param hwndParent Parent window handle.
*/
void ShowAboutDlg(HINSTANCE hInst, HWND hwndParent) {
	DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hwndParent, AboutDlgProc);
}

/**
 * Message handler for the dialog box.
 * 
 * @param  hDlg   A handle to the dialog box.
 * @param  uMsg   The message.
 * @param  wParam Additional message-specific information.
 * @param  lParam Additional message-specific information.
 * @return        TRUE if we processed the message, and FALSE if we didn't.
 */
INT_PTR CALLBACK AboutDlgProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	UNREFERENCED_PARAMETER(lParam);

	switch (uMsg) {
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;
	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL) {
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}

	return (INT_PTR)FALSE;
}
