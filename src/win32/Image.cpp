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
 * @param szPath Path to the bitmap file.
 */
void Image::LoadBitmap(LPCTSTR szPath) {
#ifdef UNDER_CE
	this->hBitmap = SHLoadDIBitmap(szPath);
#else
	this->hBitmap = (HBITMAP)LoadImage(NULL, szPath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
#endif  // UNDER_CE
}

/**
 * Loads a bitmap from a buffer.
 * 
 * @param lpBuffer Bitmap file buffer.
 */
void Image::LoadBitmap(void* lpBuffer) {
	// TODO: https://stackoverflow.com/a/2901465
#if 0
	tagBITMAPFILEHEADER bfh = *(tagBITMAPFILEHEADER*)lpBuffer;
	tagBITMAPINFOHEADER bih = *(tagBITMAPINFOHEADER*)(lpBuffer + sizeof(tagBITMAPFILEHEADER));
	RGBQUAD rgb = *(RGBQUAD*)(lpBuffer + sizeof(tagBITMAPFILEHEADER) + sizeof(tagBITMAPINFOHEADER));

	BITMAPINFO bi;
	bi.bmiColors[0] = rgb;
	bi.bmiHeader = bih;

	char* pPixels = (lpBuffer + bfh.bfOffBits);
	char* ppvBits;

	hBitmap = CreateDIBSection(NULL, &bi, DIB_RGB_COLORS, (void**)&ppvBits, NULL, 0);
	SetDIBits(NULL, hBitmap, 0, bih.biHeight, pPixels, &bi, DIB_RGB_COLORS);

	GetObject(hBitmap, sizeof(BITMAP), &cBitmap);
#endif
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
	GetObject(hBitmap, sizeof(BITMAP), &bmp);

	// Get some device contexts for the operation.
	HDC hdcScreen = GetWindowDC(NULL);
	HDC hdcNewBmp = CreateCompatibleDC(hdcScreen);
	HDC hdcOldBmp = CreateCompatibleDC(hdcScreen);

	// Get some objects together for the new bitmap.
	HBITMAP hBitmap = CreateCompatibleBitmap(hdcScreen, cx, cy);
	HGDIOBJ hOldBmp = SelectObject(hdcNewBmp, hBitmap);

	// Perform the resize operation.
	SelectObject(hdcOldBmp, hBitmap);
	StretchBlt(hdcNewBmp, 0, 0, cx, cy, hdcOldBmp, 0, 0, bmp.bmWidth,
		bmp.bmHeight, SRCCOPY);

	// Clean up.
	ReleaseDC(NULL, (HDC)hOldBmp);
	DeleteDC(hdcOldBmp);
	DeleteDC(hdcNewBmp);
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
