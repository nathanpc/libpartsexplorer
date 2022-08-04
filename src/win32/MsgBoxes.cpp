/**
 * MsgBoxes.cpp
 * Some utility functions to work with Message Boxes more easily and write less
 * boilerplate for something that is so simple.
 *
 * @author Nathan Campos <nathan@innoveworkshop.com>
 */

#include "MsgBoxes.h"

/**
 * Generic message box.
 * 
 * @param  hwndParent Parent window's handle or NULL if it doesn't have one.
 * @param  uType      Flags that control the buttons and the icon of the message box.
 * @param  szTitle    Title of the message box dialog window.
 * @param  szText     Descriptive text of the dialog box.
 * 
 * @return            ID of the button that was clicked by the user.
 */
int MsgBox(HWND hwndParent, UINT uType, LPCTSTR szTitle, LPCTSTR szText) {
	return MessageBox(hwndParent, szText, szTitle, uType);
}

/**
 * Error message box.
 * 
 * @param  hwndParent Parent window's handle or NULL if it doesn't have one.
 * @param  szTitle    Title of the message box dialog window.
 * @param  szText     Descriptive text of the dialog box.
 *
 * @return            ID of the button that was clicked by the user.
 */
int MsgBoxError(HWND hwndParent, LPCTSTR szTitle, LPCTSTR szText) {
	return MessageBox(hwndParent, szText, szTitle, MB_OK | MB_ICONERROR);
}
