/**
 * Image.h
 * Abstract representation of an image.
 * 
 * @author Nathan Campos <nathan@innoveworkshop.com>
 */

#pragma once

#include "stdafx.h"

/**
 * Image object that can be manipulated.
 */
class Image {
protected:
	HBITMAP hBitmap;

public:
	// Constructors and Destructors
	Image();
	~Image();

	// Getters and Setters
	BOOL LoadBitmap(LPCTSTR szPath);
	BOOL LoadBitmap(LPCVOID lpBuffer, SIZE_T nLen);
	HBITMAP* GetBitmapHandle();
	void DestroyBitmapHandle();

	// Manipulation
	void Resize(int cx, int cy);
};
