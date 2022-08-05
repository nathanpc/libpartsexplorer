/**
 * StringUtils.c
 * A collection of extremely using string utilities that make working with
 * strings under Windows a bit more bareable.
 *
 * @author Nathan Campos <nathan@innoveworkshop.com>
 */

#include "StringUtils.h"

#include "MsgBoxes.h"

/**
 * Converts a regular ASCII string into an Unicode string.
 * WARNING: This function allocates resources that you are responsible for
 * freeing.
 * 
 * @param  szASCII   Original ASCII string.
 * @param  szUnicode Unicode string. Allocated by this function.
 * 
 * @return           TRUE if the conversion was successful.
*/
BOOL ConvertStringAToW(const char *szASCII, WCHAR **szUnicode) {
	SIZE_T nLen = strlen(szASCII) + 1;

	// Allocate the Unicode string.
	*szUnicode = (WCHAR *)LocalAlloc(LMEM_FIXED, nLen * sizeof(WCHAR));

	// Perform the conversion.
	if (MultiByteToWideChar(CP_ACP, 0, szASCII, -1, *szUnicode, nLen) == 0) {
		LocalFree(*szUnicode);
		MsgBoxLastError(NULL);
		return FALSE;
	}

	return TRUE;
}

/**
 * Converts an Unicode string into a regular ASCII string.
 * WARNING: This function allocates resources that you are responsible for
 * freeing.
 *
 * @param  szUnicode Unicode string. Allocated by this function.
 * @param  szASCII   Original ASCII string.
 *
 * @return           TRUE if the conversion was successful.
*/
BOOL ConvertStringWToA(const WCHAR *szUnicode, char **szASCII) {
	SIZE_T nLen = wcslen(szUnicode) + 1;

	// Allocate the ASCII string.
	*szASCII = (char *)LocalAlloc(LMEM_FIXED, nLen * sizeof(char));

	// Perform the conversion.
	if (WideCharToMultiByte(CP_ACP, 0, szUnicode, -1, *szASCII, nLen, NULL, NULL) == 0) {
		LocalFree(*szASCII);
		MsgBoxLastError(NULL);
		return FALSE;
	}

	return TRUE;
}
