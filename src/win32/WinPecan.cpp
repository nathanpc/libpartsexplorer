/**
 * WinPecan.cpp
 * A C++ Windows wrapper for the Pecan C library.
 *
 * @author Nathan Campos <nathan@innoveworkshop.com>
 */

#include "WinPecan.h"

/**
 * Constructs an empty Pecan archive object.
 */
Pecan::Pecan() {
	Initialize();
}

/**
 * Constructs a Pecan archive object with data already populated from an
 * archive in the file system.
 * 
 * @param szPath Path to the Pecan archive.
 */
Pecan::Pecan(LPCTSTR szPath) {
	Initialize();
	Read(szPath);
}

/**
 * Pecan archive object destructor.
 */
Pecan::~Pecan() {
	pecan_free(&this->part);
}

/**
 * Initializes the object.
 */
void Pecan::Initialize() {
	pecan_init(&this->part);
}

/**
 * Reads an component archive and populates the object.
 * 
 * @param  szPath Path to the component archive (file or folder).
 * @return        TRUE if an error occurred.
 */
BOOL Pecan::Read(LPCTSTR szPath) {
	PECAN_ERR err;
	char *saPath;

	// Convert the path string and read the archive.
	if (!ConvertStringWToA(szPath, &saPath))
		return TRUE;
	err = pecan_read(&this->part, saPath);
	LocalFree(saPath);

	return FALSE;
}

/**
 * Writes an component archive to disk.
 * 
 * @param  szPath Path to the component archive file to write to.
 * @return        TRUE if an error occurred.
 */
BOOL Pecan::Write(LPCTSTR szPath) {
	PECAN_ERR err;
	char *saPath;

	// Convert the path string and read the archive.
	if (!ConvertStringWToA(szPath, &saPath))
		return TRUE;
	err = pecan_write(&this->part, saPath);
	LocalFree(saPath);

	return FALSE;
}

/**
 * Gets the number of attributes available for a given type.
 * 
 * @param  attrType Type of the attribute to get the count from.
 * @return          Number of attributes available.
 */
SIZE_T Pecan::AttributesCount(PECAN_ATTR_TYPE attrType) {
	return pecan_get_attr_len(&this->part, attrType);
}

/**
 * Gets an attribute by its index.
 * 
 * @param  attrType Type of the attribute.
 * @param  nIndex   Index of the attribute you want to get.
 * 
 * @return          Requested attribute.
 */
PecanAttribute Pecan::GetAttribute(PECAN_ATTR_TYPE attrType, SIZE_T nIndex) {
	PecanAttribute attr(pecan_get_attr_idx(&this->part, attrType, nIndex));
	return attr;
}

/**
 * Gets an attribute by its name.
 * 
 * @param  attrType Type of the attribute.
 * @param  szName   Name of the attribute you want to get.
 * 
 * @return          Requested attribute.
 */
PecanAttribute Pecan::GetAttribute(PECAN_ATTR_TYPE attrType, LPCTSTR szName) {
	char *saName;

	// Convert the string.
	if (!ConvertStringWToA(szName, &saName)) {
		PecanAttribute attr(NULL);
		return attr;
	}
	
	// Get the attribute and clean up.
	PecanAttribute attr(pecan_get_attr(&this->part, attrType, saName));
	LocalFree(saName);

	return attr;
}

/**
 * Shows a message box with the last error message produced by the Pecan API.
 */
void Pecan::ShowLastErrorMessage() {
	LPTSTR szMsg;

	// Convert the error message into an Unicode string.
	if (!ConvertStringAToW(pecan_err_msg(), &szMsg))
		return;

	// Display the error message and clean ourselves up.
	MsgBoxError(NULL, _T("Pecan Error"), szMsg);
	LocalFree(szMsg);
}

/**
 * Pecan blank attribute constructor.
 */
PecanAttribute::PecanAttribute() {
	this->attr = (pecan_attr_t *)malloc(sizeof(pecan_attr_t));
	attr_init(this->attr);
}

/**
 * Constructs a Pecan attribute object with an attribute already assigned to it.
 * 
 * @param attr Attribute to be associated with this object.
 */
PecanAttribute::PecanAttribute(pecan_attr_t *attr) {
	this->attr = attr;
}

/**
 * Gets the name of the attribute.
 * WARNING: This function allocates a string that you're responsible to free.
 * 
 * @return Name of the attribute. (Allocated and must be free'd by user)
 */
LPTSTR PecanAttribute::GetName() {
	LPTSTR szName;

	// Convert the string.
	if (!ConvertStringAToW(this->attr->name, &szName))
		return NULL;

	return szName;
}

/**
 * Sets the name of the attribute.
 * 
 * @param szName New name of the attribute.
 */
void PecanAttribute::SetName(LPCTSTR szName) {
	char *saName;

	// Convert the string.
	if (!ConvertStringWToA(szName, &saName))
		return;

	// Set the property and free the temporary buffer.
	attr_set_name(this->attr, saName);
	LocalFree(saName);
}

/**
 * Gets the value of the attribute.
 * WARNING: This function allocates a string that you're responsible to free.
 * 
 * @return Value of the attribute. (Allocated and must be free'd by user)
 */
LPTSTR PecanAttribute::GetValue() {
	LPTSTR szValue;

	// Convert the string.
	if (!ConvertStringAToW(this->attr->value, &szValue))
		return NULL;

	return szValue;
}

/**
 * Sets the value of the attribute.
 * 
 * @param szValue New value of the attribute.
 */
void PecanAttribute::SetValue(LPCTSTR szValue) {
	char *saValue;

	// Convert the string.
	if (!ConvertStringWToA(szValue, &saValue))
		return;

	// Set the property and free the temporary buffer.
	attr_set_value(this->attr, saValue);
	LocalFree(saValue);
}

/**
 * Is this attribute valid?
 * 
 * @return TRUE if we actually have an attribute associated with the object.
 */
BOOL PecanAttribute::IsValid() {
	return this->attr != NULL;
}
