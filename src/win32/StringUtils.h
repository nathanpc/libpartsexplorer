/**
 * StringUtils.h
 * A collection of extremely using string utilities that make working with
 * strings under Windows a bit more bareable.
 * 
 * @author Nathan Campos <nathan@innoveworkshop.com>
 */

#pragma once

#ifdef  __cplusplus
extern "C" {
#endif  // __cplusplus

#include "stdafx.h"

BOOL ConvertStringAToW(const char *szASCII, WCHAR **szUnicode);
BOOL ConvertStringWToA(const WCHAR *szUnicode, char **szASCII);

#ifdef  __cplusplus
}
#endif  // __cplusplus
