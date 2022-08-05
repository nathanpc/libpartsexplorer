/**
 * WinPecan.h
 * A C++ Windows wrapper for the Pecan C library.
 *
 * @author Nathan Campos <nathan@innoveworkshop.com>
 */

#pragma once

#include "stdafx.h"
#include "../pecan.h"

// Windows API-ize some things.
#define PECAN_ERR       pecan_err_t
#define PECAN_ATTR      pecan_attr_t
#define PECAN_ATTR_TYPE pecan_attr_type_t

/**
 * Pecan component attribute.
 */
class PecanAttribute {
protected:
	pecan_attr_t *attr;

public:
	// Constructors and Destructors
	PecanAttribute();
	PecanAttribute(pecan_attr_t *attr);

	// Getters and Setters
	LPTSTR GetName();
	void SetName(LPCTSTR szName);
	LPTSTR GetValue();
	void SetValue(LPCTSTR szValue);

	// Validation
	BOOL IsValid();
};

/**
 * The helper class to deal with your electronic components definitions.
 */
class Pecan {
protected:
	pecan_archive_t part;

public:
	// Constructors and Destructors
	Pecan();
	Pecan(LPCTSTR szPath);
	virtual ~Pecan();

	// Read and Write
	BOOL Read(LPCTSTR szPath);
	BOOL Write(LPCTSTR szPath);

	// Attributes
	SIZE_T AttributesCount(PECAN_ATTR_TYPE attrType);
	PecanAttribute GetAttribute(PECAN_ATTR_TYPE attrType, SIZE_T nIndex);
	PecanAttribute GetAttribute(PECAN_ATTR_TYPE attrType, LPCTSTR szName);

	// Error Handling
	void ShowLastErrorMessage();

private:
	void Initialize();
};
