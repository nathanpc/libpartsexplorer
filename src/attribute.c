/**
 * attribute.c
 * Collections of utilities to deal with component attributes.
 *
 * @author Nathan Campos <nathan@innoveworkshop.com>
 */

#include "attribute.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Initializes an component attribute structure.
 *
 * @param attr Attribute structure to be initialized.
 */
void attr_init(pecan_attr_t *attr) {
	attr->name = NULL;
	attr->value = NULL;
}

/**
 * Sets the name of the attribute.
 *
 * @param attr Attribute to be changed.
 * @param name New name of the attribute.
 */
void attr_set_name(pecan_attr_t *attr, const char *name) {
	// Make sure we have enough space to store our attribute.
	free(attr->name);
	attr->name = (char *)malloc((strlen(name) + 1) * sizeof(char));

	// Actually set the attribute.
	strcpy(attr->name, name);
}

/**
 * Sets the name of the attribute.
 *
 * @param attr  Attribute to be changed.
 * @param start Pointer to the start of the new name of the attribute.
 * @param end   Pointer to the start of the new name of the attribute.
 */
void attr_set_name_tk(pecan_attr_t *attr, const char *start, const char *end) {
	char *buftmp;
	const char *tmp;

	// Make sure we have enough space to store our attribute.
	free(attr->name);
	attr->name = (char *)malloc((end - start + 1) * sizeof(char));

	// Copy the token to the attribute.
	buftmp = attr->name;
	tmp = start;
	while (tmp != end) {
		*buftmp++ = *tmp++;
	}
	*buftmp = '\0';
}

/**
 * Sets the name of the attribute.
 *
 * @param attr  Attribute to be changed.
 * @param value New value of the attribute.
 */
void attr_set_value(pecan_attr_t *attr, const char *value) {
	// Make sure we have enough space to store our attribute.
	free(attr->value);
	attr->value = (char *)malloc((strlen(value) + 1) * sizeof(char));

	// Actually set the attribute.
	strcpy(attr->value, value);
}

/**
 * Sets the value of the attribute.
 *
 * @param attr  Attribute to be changed.
 * @param start Pointer to the start of the new value of the attribute.
 * @param end   Pointer to the start of the new value of the attribute.
 */
void attr_set_value_tk(pecan_attr_t *attr, const char *start, const char *end) {
	char *buftmp;
	const char *tmp;

	// Make sure we have enough space to store our attribute.
	free(attr->value);
	attr->value = (char *)malloc((end - start + 1) * sizeof(char));

	// Copy the token to the attribute.
	buftmp = attr->value;
	tmp = start;
	while (tmp != end) {
		*buftmp++ = *tmp++;
	}
	*buftmp = '\0';
}

/**
 * Gets an attribute in the proper format to be written to an attributes file
 * already with a newline at the end.
 * WARNING: This function allocates its return string, so you're responsible
 *          for freeing it.
 *
 * @param  attr Attribute to be formatted.
 * @param  buf  Pointer to the formatted string. (WARNING: Allocated internally)
 * @return      Size of the formatted attribute string or 0 if an error occured.
 */
size_t attr_get_file_format(pecan_attr_t attr, char **buf) {
	// Calculate the length of the final string.
	size_t len = 2 + strlen(attr.name) + strlen(attr.value);

	// Allocate some space and copy the string over.
	*buf = (char *)realloc(*buf, (len + 1) * sizeof(char));
	if (*buf == NULL)
		return 0;
	sprintf(*buf, "%s\t%s\n", attr.name, attr.value);

	return len;
}

/**
 * Gets all of the attributes in an array and gives back the contents to write
 * it back to an attributes file.
 * WARNING: This function allocates its return string, so you're responsible
 *          for freeing it.
 *
 * @param  attribs Attributes array to be written to a file.
 * @param  buf     Pointer to the file contents. (WARNING: Allocated internally)
 * @return         Size of the file content string or 0 if an error occured.
 */
size_t attr_get_file(pecan_attr_arr_t attribs, char **buf) {
	pecan_attr_t *it;
	char *tmpbuf;
	size_t len;

	// Reset things up.
	*buf = NULL;
	len = 1;

	// Iterate over the attributes populating the contents buffer.
	for (it = cvector_begin(attribs); it != cvector_end(attribs); ++it) {
		char *abuf;
		size_t alen;

		// Get a new attribute line for the file.
		abuf = NULL;
		alen = attr_get_file_format(*it, &abuf);

		// Allocate enough space to hold our content.
		len += alen;
		*buf = (char *)realloc(*buf, len * sizeof(char));
		tmpbuf = (*buf) + len - alen - 1;

		// Concatenate the new attribute to the existing content.
		while (*abuf != '\0') {
			*tmpbuf = *abuf;

			tmpbuf++;
			abuf++;
		}

		// Clean up our mess.
		abuf -= alen;
		free(abuf);
	}

	// NULL terminate the string and return.
	*tmpbuf = '\0';
	return len;
}

/**
 * Frees up any resources allocated by the attribute.
 *
 * @param attr Attribute to have its contents free'd.
 */
void attr_free(pecan_attr_t attr) {
	free(attr.name);
	attr.name = NULL;
	free(attr.value);
	attr.value = NULL;
}
