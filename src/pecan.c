/**
 * pecan.c
 * The helper library to deal with your electronic components definitions.
 *
 * @author Nathan Campos <nathan@innoveworkshop.com>
 */

#include "pecan.h"

#include <cvector_utils.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Initializes an component structure.
 *
 * @param  part Component structure to be initialized.
 * @return      PECAN_OK if the operation was successful.
 */
pecan_err_t pecan_init(pecan_archive_t *part) {
	// NULL out everything.
	part->fname = NULL;
	part->attribs = NULL;

	return PECAN_OK;
}

/**
 * Reads an component archive and populates the archive structure.
 *
 * @param  part  Empty component archive to be populated.
 * @param  fname Path to the component archive file.
 * @return       PECAN_OK if the operation was successful.
 */
pecan_err_t pecan_read(pecan_archive_t *part, const char *fname) {
	return PECAN_ERR_UNKNOWN;
}

/**
 * Writes an component archive from an archive structure.
 *
 * @param  part  Component archive structure to be saved to disk.
 * @param  fname Path to the component archive file to write to.
 * @return       PECAN_OK if the operation was successful.
 */
pecan_err_t pecan_write(pecan_archive_t *part, const char *fname) {
	return PECAN_ERR_UNKNOWN;
	mtar_t tar;
	const char *str1 = "Hello world";
	const char *str2 = "Goodbye world";

	mtar_open(&tar, "/home/nathan/dev/parts-explorer/example/example.tar", "w");

	/* Write strings to files `test1.txt` and `test2.txt` */
	mtar_write_file_header(&tar, "test1.txt", strlen(str1));
	mtar_write_data(&tar, str1, strlen(str1));
	mtar_write_file_header(&tar, "test2.txt", strlen(str2));
	mtar_write_data(&tar, str2, strlen(str2));

	/* Finalize -- this needs to be the last thing done before closing */
	mtar_finalize(&tar);

	/* Close archive */
	mtar_close(&tar);

	return PECAN_ERR_UNKNOWN;
}

/**
 * Adds an attribute to the component without checking if it already exists.
 *
 * @param part  Component archive structure.
 * @param name  Name of the attribute.
 * @param value Value of the attribute.
 */
void pecan_add_attr(pecan_archive_t *part, const char *name, const char *value) {
	pecan_attr_t attr;

	// Create and populate the attribute.
	attr_init(&attr);
	attr_set_name(&attr, name);
	attr_set_value(&attr, value);

	// Push the attribute into the vector.
	cvector_push_back(part->attribs, attr);
}

/**
 * Sets an attribute from the component by its name. If it doesn't exist yet
 * it'll be created.
 *
 * @param part  Component archive structure.
 * @param name  Name of the attribute to be set.
 * @param value Value of the attribute to be set to.
 */
void pecan_set_attr(pecan_archive_t *part, const char *name, const char *value) {
	// Try to get the attribute.
	pecan_attr_t *attr = pecan_get_attr(part, name);

	// Should we create a new attribute?
	if (!attr) {
		pecan_add_attr(part, name, value);
		return;
	}

	// Set the value of an existing attribute.
	attr_set_value(attr, value);
}

/**
 * Gets an attribute from the component by its name.
 *
 * @param  part Component archive structure.
 * @param  name Name of the attribute to be found.
 * @return      Attribute found in the component or NULL if one wasn't found.
 */
pecan_attr_t *pecan_get_attr(pecan_archive_t *part, const char *name) {
	// Check if we have anything in the attributes vector.
	if (part->attribs) {
		pecan_attr_t *it;

		// Iterate over the attributes trying to find a matching attribute name.
		for (it = cvector_begin(part->attribs); it != cvector_end(part->attribs); ++it) {
			// Check if the names match.
			if (strcmp(it->name, name) == 0)
				return it;
		}
	}

	// No attribute with this name was found.
	return NULL;
}

/**
 * Frees up any resources allocated by the archive structure.
 *
 * @param part Component archive to have its contents free'd.
 */
void pecan_free(pecan_archive_t *part) {
	// Free our path name.
	free(part->fname);
	part->fname = NULL;

	// Free up all of our attributes.
	cvector_free_each_and_free(part->attribs, attr_free);
}
