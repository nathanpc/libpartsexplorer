/**
 * Image.cpp
 * Abstract representation of an image.
 *
 * @author Nathan Campos <nathan@innoveworkshop.com>
 */

#include "Image.h"

/**
 * Constructs an empty image object.
 */
Image::Image() {
	this->hBitmap = NULL;
}

/**
 * Destroys the object.
 */
Image::~Image() {
	DestroyBitmapHandle();
}

/**
 * Loads a bitmap from a file.
 *
 * @param  szPath Path to the bitmap file.
 * @return        TRUE if the operation was successful.
 */
BOOL Image::LoadBitmap(LPCTSTR szPath) {
#ifdef UNDER_CE
	this->hBitmap = SHLoadDIBitmap(szPath);
#else
	this->hBitmap = (HBITMAP)LoadImage(NULL, szPath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
#endif  // UNDER_CE

	return this->hBitmap != NULL;
}

/**
 * Loads a bitmap from a buffer.
 * 
 * @param  lpBuffer Bitmap file buffer.
 * @param  nLen     Length of the buffer.
 * 
 * @return          TRUE if the operation was successful.
 */
BOOL Image::LoadBitmap(LPCVOID lpBuffer, SIZE_T nLen) {
	TCHAR szTempFile[MAX_PATH];

	// Create a temporary file.
	if (!CreateTempFileContent(szTempFile, lpBuffer, nLen))
		return FALSE;

	// Load the temporary bitmap file.
	if (!LoadBitmap(szTempFile))
		return FALSE;

	// Delete the temporary file.
	DeleteFile(szTempFile);

	return TRUE;
}

/**
 * Resizes the associated image.
 * 
 * @param cx New width.
 * @param cy New height.
 */
void Image::Resize(int cx, int cy) {
	// Get the original bitmap into a structure.
	BITMAP bmp = { 0 };
	GetObject(this->hBitmap, sizeof(BITMAP), &bmp);

	// Get some device contexts for the operation.
	HDC hdcScreen = GetWindowDC(NULL);
	HDC hdcNewBmp = CreateCompatibleDC(hdcScreen);
	HDC hdcOldBmp = CreateCompatibleDC(hdcScreen);

	// Get some objects together for the new bitmap.
	HBITMAP hNewBitmap = CreateCompatibleBitmap(hdcScreen, cx, cy);
	HGDIOBJ hOldBmp = SelectObject(hdcNewBmp, hNewBitmap);

	// Perform the resize operation.
	SelectObject(hdcOldBmp, this->hBitmap);
	StretchBlt(hdcNewBmp, 0, 0, cx, cy, hdcOldBmp, 0, 0, bmp.bmWidth,
		bmp.bmHeight, SRCCOPY);

	// Clean up.
	ReleaseDC(NULL, (HDC)hOldBmp);
	DeleteDC(hdcOldBmp);
	DeleteDC(hdcNewBmp);
	DeleteObject(this->hBitmap);

	// Use the new bitmap handle.
	this->hBitmap = hNewBitmap;
}

/**
 * Gets the bitmap handle for the associated image.
 * 
 * @return Associated bitmap handle.
 */
HBITMAP* Image::GetBitmapHandle() {
	if (this->hBitmap == NULL)
		return NULL;

	return &this->hBitmap;
}

/**
 * Destroys the internal bitmap handle.
 */
void Image::DestroyBitmapHandle() {
	// If the handle has already been destroyed do nothing.
	if (this->hBitmap == NULL)
		return;

	// Destroy the handle object.
	DeleteObject(this->hBitmap);
	this->hBitmap = NULL;
}
