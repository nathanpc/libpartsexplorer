/**
 * TempFileUtils.c
 * Some utilities to deal with temporary files under Windows.
 *
 * @author Nathan Campos <nathan@innoveworkshop.com>
 */

#include "TempFileUtils.h"

/**
 * Creates a temporary file for us to use.
 * WARNING: This function allocates a file handle. You are responsible for closing it.
 *
 * @param  lpTempFilename Pointer to the string that will contain the temp filename.
 * @return                Temporary file handle. (Allocated by the function. Free'd by you.)
 */
HANDLE CreateTempFile(LPTSTR lpTempFilename) {
    TCHAR szTempPath[MAX_PATH];
    DWORD dwRetVal;
    UINT uRetVal;
    HANDLE hTempFile = INVALID_HANDLE_VALUE;

    // Get the path to the temp folder.
    dwRetVal = GetTempPath(MAX_PATH, szTempPath);
    if ((dwRetVal > MAX_PATH) || (dwRetVal == 0)) {
        MsgBoxLastError(NULL);
        return INVALID_HANDLE_VALUE;
    }

    // Generates a temporary file name.
    uRetVal = GetTempFileName(szTempPath, _T("Pecan"), 0, lpTempFilename);
    if (uRetVal == 0) {
        MsgBoxLastError(NULL);
        return INVALID_HANDLE_VALUE;
    }

    // Creates the new file to write to for the upper-case version.
    hTempFile = CreateFile(lpTempFilename, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS,
        FILE_ATTRIBUTE_NORMAL, NULL);
    if (hTempFile == INVALID_HANDLE_VALUE) {
        MsgBoxLastError(NULL);
        return INVALID_HANDLE_VALUE;
    }

    return hTempFile;
}

/**
 * Creates a temporary file populated with content.
 *
 * @param  lpTempFilename Pointer to the string that will contain the temp filename.
 * @param  lpBuffer       Buffer to the contents of the file.
 * @param  nLen           Number of bytes to write to the file.
 *
 * @return                TRUE if the operation was successful.
 */
BOOL CreateTempFileContent(LPTSTR lpTempFilename, LPCVOID lpBuffer, SIZE_T nLen) {
    HANDLE hFile;
    DWORD dwBytesWritten;

    // Create our temporary file.
    hFile = CreateTempFile(lpTempFilename);
    if (hFile == INVALID_HANDLE_VALUE)
        return FALSE;

    // Write to the file.
    if (!WriteFile(hFile, lpBuffer, nLen, &dwBytesWritten, NULL)) {
        CloseHandle(hFile);
        MsgBoxLastError(NULL);
        return FALSE;
    }

    // Close the temporary file handle.
    if (!CloseHandle(hFile)) {
        MsgBoxLastError(NULL);
        return FALSE;
    }

    return TRUE;
}
