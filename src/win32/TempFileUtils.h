/**
 * TempFileUtils.h
 * Some utilities to deal with temporary files under Windows.
 *
 * @author Nathan Campos <nathan@innoveworkshop.com>
 */

#pragma once

#ifdef  __cplusplus
extern "C" {
#endif  // __cplusplus

#include "stdafx.h"

// Temporary Files
HANDLE CreateTempFile(LPTSTR lpTempFilename);
BOOL CreateTempFileContent(LPTSTR lpTempFilename, LPCVOID lpBuffer, SIZE_T nLen);

#ifdef  __cplusplus
}
#endif  // __cplusplus
