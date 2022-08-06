/**
 * WinPecan
 * Windows application to help you deal with your Pecan archives.
 *
 * @author Nathan Campos <nathan@innoveworkshop.com>
 */

#include "MainWindow.h"

#include "AboutDlg.h"
#include "DetailView.h"

// Window sizing definitions.
#define WND_WIDTH  500
#define WND_HEIGHT 400

// Private variables.
TCHAR szTitle[MAX_LOADSTRING];
TCHAR szWindowClass[MAX_LOADSTRING];

// Private methods.
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

/**
 * Application's main entry point.
 * 
 * @param  hInstance     A handle to the current instance of the application.
 * @param  hPrevInstance A handle to the previous instance of the application.
 * @param  lpCmdLine     Command line arguments excluding the program name.
 * @param  nCmdShow      Controls how the window is to be shown.
 * 
 * @return               Return code.
*/
int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow) {
	MSG msg;
	HACCEL hAccelTable;

	// Set some things up.
	g_hInst = hInstance;

	// Load strings from resource.
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_PECAN, szWindowClass, MAX_LOADSTRING);

	// Register the window class.
	if (!RegisterWndClass()) {
		MsgBoxError(NULL, _T("Window Class Register Error"),
			_T("An error occurred while trying to register the window class."));
		return FALSE;
	}

	// Initialize the application.
	if (!InitInstance(nCmdShow)) {
		MsgBoxError(NULL, _T("Window Initialization Error"),
			_T("An error occurred while trying to initialize the window."));
		return FALSE;
	}

	// Load the accelerator tabole.
	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_PECAN));

	// Application's main message loop.
	while (GetMessage(&msg, NULL, 0, 0)) {
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int)msg.wParam;
}

/**
 * Registers the window class.
 * 
 * @return Class atom that uniquely identifies us, or 0 if an error occurred.
*/
ATOM RegisterWndClass() {
	WNDCLASSEX wcex;

	wcex.cbSize        = sizeof(WNDCLASSEX);
	wcex.style         = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc   = WndProc;
	wcex.cbClsExtra    = 0;
	wcex.cbWndExtra    = 0;
	wcex.hInstance     = g_hInst;
	wcex.hIcon         = LoadIcon(g_hInst, MAKEINTRESOURCE(IDI_PECAN));
	wcex.hCursor       = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName  = MAKEINTRESOURCE(IDC_PECAN);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm       = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

/**
 * Creates and shows the main application window.
 * 
 * @param  nCmdShow Controls how the window is to be shown.
 * @return          TRUE if the window creation was successful.
*/
BOOL InitInstance(int nCmdShow) {
	// Create our main window.
	g_hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, WND_WIDTH, WND_HEIGHT, NULL, NULL, g_hInst, NULL);
	if (!g_hWnd)
		return FALSE;

	// Populate the window with controls.
	if (!PopulateWindow())
		return FALSE;

	// Make sure we are ready to handle things.
	uiManager.SetInstance(&g_hInst);
	uiManager.SetMainWindowHandle(&g_hWnd);

	// Show and redraw the window.
	ShowWindow(g_hWnd, nCmdShow);
	UpdateWindow(g_hWnd);

	return TRUE;
}

/**
 * Populates the window with controls.
 * 
 * @return TRUE if everything was successful.
 */
BOOL PopulateWindow() {
	// Calculate the detail view dialog size and position.
	RECT rcDetailView;
	GetClientRect(g_hWnd, &rcDetailView);
	rcDetailView.bottom -= DEFAULT_UI_MARGIN;
	rcDetailView.left   += DEFAULT_UI_MARGIN;
	rcDetailView.right  -= rcDetailView.left + DEFAULT_UI_MARGIN;

	// Create the detail view.
	CreateDetailView(g_hInst, &g_hWnd, rcDetailView);

	return TRUE;
}

/**
 * Message handler for the window.
 *
 * @param  hDlg   A handle to the window.
 * @param  uMsg   The message.
 * @param  wParam Additional message-specific information.
 * @param  lParam Additional message-specific information.
 * @return        Result of the message processing. (Depends on the message sent)
 */
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	int wmId, wmEvent;

	switch (uMsg) {
	case WM_COMMAND:
		wmId = LOWORD(wParam);
		wmEvent = HIWORD(wParam);

		switch (wmId) {
		case IDM_FILE_OPENARCHIVE:
			// Open archive.
			MenuOpenArchive(hWnd, uMsg, wParam, lParam);
			break;
		case IDM_ABOUT:
			// Show about dialog.
			ShowAboutDlg(g_hInst, g_hWnd);
			break;
		case IDM_EXIT:
			// Exit the application.
			WndMainClose(hWnd, uMsg, wParam, lParam);
			break;
		default:
			// Handle WM_COMMAND for everything else.
			return DefWindowProc(hWnd, uMsg, wParam, lParam);
		}
		break;
	case WM_SIZE:
		// Resizing the window.
		ResizeDetailView(hWnd, uMsg, wParam, lParam);
		break;
	case WM_DESTROY:
		// Destroys the window.
		WndMainDestroy(hWnd, uMsg, wParam, lParam);
		break;
	default:
		// Default message handler.
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}

	return (LRESULT)0;
}

/**
 * Sends messages to close the main window.
*/
LRESULT WndMainClose(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	DestroyDetailView();
	DestroyWindow(hWnd);
	return 0;
}

/**
 * Process the WM_DESTROY message for the window.
 */
LRESULT WndMainDestroy(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	PostQuitMessage(0);
	return 0;
}

/**
 * Open Archive menu item event handler.
 */
LRESULT MenuOpenArchive(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	return uiManager.OpenArchiveInteractive();
}
