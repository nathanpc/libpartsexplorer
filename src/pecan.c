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

#include "fileutils.h"
#include "parser.h"
#include "error.h"

// Handle microtar errors.
#define HANDLE_MTAR_ERR(mterr)                                                \
	do {                                                                      \
		if (mterr) {                                                          \
			err_format_msg(EMSG("microtar error: %s"), mtar_strerror(mterr)); \
			err = PECAN_ERR_FILE_IO;                                          \
			goto cleanup;                                                     \
		}                                                                     \
	} while (0)

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
	part->params = NULL;

	// Initialize what needs to be initialized.
	err_init();
	blob_init(&part->image);
	blob_init(&part->datasheet);

	return PECAN_OK;
}

/**
 * Reads an component archive and populates the archive structure.
 *
 * @param  part  Empty component archive to be populated.
 * @param  fpath Path to the component archive (file or folder).
 * @return       PECAN_OK if the operation was successful.
 *               PECAN_ERR_PATH_NOT_FOUND if the specified path wasn't found.
 *               PECAN_ERR_FILE_IO if the archive was corrupted.
 *               PECAN_ERR_PARSE if there were parsing errors.
 */
pecan_err_t pecan_read(pecan_archive_t *part, const char *fpath) {
	// Check if we even have something there.
	if (!file_exists(fpath)) {
		err_format_msg(EMSG("Specified archive path '%s' not found"),
			fpath);
		return PECAN_ERR_PATH_NOT_FOUND;
	}

	// Are we dealing with an unpacked archive?
	if (is_dir(fpath))
		return pecan_read_unpacked(part, fpath);
	
	return pecan_read_packed(part, fpath);
}

/**
 * Writes an component archive from an archive structure.
 *
 * @param  part  Component archive structure to be saved to disk.
 * @param  fname Path to the component archive file to write to.
 * @return       PECAN_OK if the operation was successful.
 *               PECAN_ERR_PATH_NOT_FOUND if the specified path wasn't writable.
 *               PECAN_ERR_FILE_IO if there were errors while trying to write.
 */
pecan_err_t pecan_write(pecan_archive_t *part, const char *fname) {
	size_t clen;
	mtar_t tar;
	char *contents = NULL;
	pecan_err_t err = PECAN_OK;
	int mterr = MTAR_ESUCCESS;

	// Open archive for writing.
	mterr = mtar_open(&tar, fname, "w");
	HANDLE_MTAR_ERR(mterr);

	// Write manifest to the archive.
	clen = attr_get_file(part->attribs, &contents);
	mtar_write_file_header(&tar, PECAN_MANIFEST_FILE, clen);
	HANDLE_MTAR_ERR(mterr);
	mtar_write_data(&tar, contents, clen);
	HANDLE_MTAR_ERR(mterr);
	free(contents);
	contents = NULL;

	// Write parameters to the archive.
	clen = attr_get_file(part->params, &contents);
	mtar_write_file_header(&tar, PECAN_PARAM_FILE, clen);
	HANDLE_MTAR_ERR(mterr);
	mtar_write_data(&tar, contents, clen);
	HANDLE_MTAR_ERR(mterr);
	free(contents);
	contents = NULL;

	// Write component image to the archive.
	if (part->image.len > 0) {
		mtar_write_file_header(&tar, PECAN_IMAGE_FILE, part->image.len);
		HANDLE_MTAR_ERR(mterr);
		mtar_write_data(&tar, part->image.data, part->image.len);
		HANDLE_MTAR_ERR(mterr);
	}

	// Write component datasheet to the archive.
	if (part->datasheet.len > 0) {
		mtar_write_file_header(&tar, PECAN_DATASHEET_FILE, part->datasheet.len);
		HANDLE_MTAR_ERR(mterr);
		mtar_write_data(&tar, part->datasheet.data, part->datasheet.len);
		HANDLE_MTAR_ERR(mterr);
	}

	// Finalize and close the archive.
	mtar_finalize(&tar);
cleanup:
	mtar_close(&tar);

	free(contents);
	return err;
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
	cvector_free_each_and_free(part->params, attr_free);

	// Free up our blobs.
	blob_free(&part->image);
	blob_free(&part->datasheet);

	// Clean up our error message stuff.
	err_free();
}

/**
 * Adds an attribute to the component without checking if it already exists.
 *
 * @param part  Component archive structure.
 * @param type  Type of attribute.
 * @param attr  Attribute to be added to the list.
 */
void pecan_add_attr(pecan_archive_t *part, pecan_attr_type_t type,
					pecan_attr_t attr) {
	// Push the attribute into the vector.
	switch (type) {
	case PECAN_MANIFEST:
		cvector_push_back(part->attribs, attr);
		break;
	case PECAN_PARAMETERS:
		cvector_push_back(part->params, attr);
		break;
	}
}

/**
 * Adds an attribute to the component without checking if it already exists.
 *
 * @param part  Component archive structure.
 * @param type  Type of attribute.
 * @param name  Name of the attribute.
 * @param value Value of the attribute.
 */
void pecan_add_attr_str(pecan_archive_t *part, pecan_attr_type_t type,
						const char *name, const char *value) {
	pecan_attr_t attr;

	// Create and populate the attribute.
	attr_init(&attr);
	attr_set_name(&attr, name);
	attr_set_value(&attr, value);

	// Push the attribute into the vector.
	pecan_add_attr(part, type, attr);
}

/**
 * Sets an attribute from the component by its name. If it doesn't exist yet
 * it'll be created.
 *
 * @param part  Component archive structure.
 * @param type  Type of attribute.
 * @param name  Name of the attribute to be set.
 * @param value Value of the attribute to be set to.
 */
void pecan_set_attr(pecan_archive_t *part, pecan_attr_type_t type,
					const char *name, const char *value) {
	// Try to get the attribute.
	pecan_attr_t *attr = pecan_get_attr(part, type, name);

	// Should we create a new attribute?
	if (!attr) {
		pecan_add_attr_str(part, type, name, value);
		return;
	}

	// Set the value of an existing attribute.
	attr_set_value(attr, value);
}

/**
 * Gets an attribute from the component by its name.
 *
 * @param  part Component archive structure.
 * @param  type Type of attribute.
 * @param  name Name of the attribute to be found.
 * @return      Attribute found in the component or NULL if one wasn't found.
 */
pecan_attr_t *pecan_get_attr(pecan_archive_t *part, pecan_attr_type_t type,
							 const char *name) {
	pecan_attr_t *attrs;
	switch (type) {
		case PECAN_MANIFEST:
			attrs = part->attribs;
			break;
		case PECAN_PARAMETERS:
			attrs = part->params;
			break;
	}

	// Check if we have anything in the attributes vector.
	if (attrs) {
		pecan_attr_t *it;

		// Iterate over the attributes trying to find a matching attribute name.
		for (it = cvector_begin(attrs); it != cvector_end(attrs); ++it) {
			// Check if the names match.
			if (strcmp(it->name, name) == 0)
				return it;
		}
	}

	// No attribute with this name was found.
	return NULL;
}

/**
 * Gets an attribute from the component by its index.
 *
 * @param  part  Component archive structure.
 * @param  type  Type of attribute.
 * @param  index Index of the attribute to fetch.
 * @return       The requested attribute or NULL if the index is out-of-range.
 */
pecan_attr_t *pecan_get_attr_idx(pecan_archive_t *part, pecan_attr_type_t type,
								 size_t index) {
	pecan_attr_t *attrs;
	switch (type) {
		case PECAN_MANIFEST:
			attrs = part->attribs;
			break;
		case PECAN_PARAMETERS:
			attrs = part->params;
			break;
	}

	// Check if the index is valid.
	if (index >= cvector_size(attrs))
		return NULL;

	// Return our attribute.
	return &attrs[index];
}

/**
 * Gets the number of attributes of the component.
 *
 * @param  part Component archive structure.
 * @param  type Type of attribute.
 * @return      Number of attributes stored in the component archive.
 */
size_t pecan_get_attr_len(pecan_archive_t *part, pecan_attr_type_t type) {
	pecan_attr_t *attrs;
	switch (type) {
		case PECAN_MANIFEST:
			attrs = part->attribs;
			break;
		case PECAN_PARAMETERS:
			attrs = part->params;
			break;
	}

	return cvector_size(attrs);
}

/**
 * Reads an component archive and populates the archive structure.
 *
 * @param  part  Empty component archive to be populated.
 * @param  fname Path to the component archive file.
 * @return       PECAN_OK if the operation was successful.
 *               PECAN_ERR_PATH_NOT_FOUND if the specified path wasn't found.
 *               PECAN_ERR_FILE_IO if the archive was corrupted.
 *               PECAN_ERR_PARSE if there were parsing errors.
 */
pecan_err_t pecan_read_packed(pecan_archive_t *part, const char *fname) {
	mtar_t tar;
	mtar_header_t header;
	char *contents = NULL;
	pecan_err_t err = PECAN_OK;
	int mterr = MTAR_ESUCCESS;

	// Open archive for reading.
	mtar_open(&tar, fname, "r");

	// TODO: Use mtar_next()

	// Get the manifest from the archive.
	mterr = mtar_find(&tar, PECAN_MANIFEST_FILE, &header);
	if (mterr != MTAR_ESUCCESS) {
		err_set_msg(EMSG("Couldn't get the manifest file from the archive"));
		err = PECAN_ERR_FILE_IO;
		goto cleanup;
	}

	// Parse the manifest.
	contents = (char *)realloc(contents, header.size + 1);
	mtar_read_data(&tar, contents, header.size);
	HANDLE_MTAR_ERR(mterr);
	err = parse_attributes(part, PECAN_MANIFEST, contents);
	if (err)
		goto cleanup;

	// Get the parameters from the archive.
	mterr = mtar_find(&tar, PECAN_PARAM_FILE, &header);
	if (mterr != MTAR_ESUCCESS) {
		err_set_msg(EMSG("Couldn't get the parameters file from the archive"));
		err = PECAN_ERR_FILE_IO;
		goto cleanup;
	}

	// Parse the parameters.
	contents = (char *)realloc(contents, header.size + 1);
	mtar_read_data(&tar, contents, header.size);
	HANDLE_MTAR_ERR(mterr);
	err = parse_attributes(part, PECAN_PARAMETERS, contents);
	if (err)
		goto cleanup;

	// Get the component image from the archive.
	mterr = mtar_find(&tar, PECAN_IMAGE_FILE, &header);
	if (mterr == MTAR_ESUCCESS) {
		mterr = blob_tar_read(&part->image, &tar, header);
		HANDLE_MTAR_ERR(mterr);
	}

	// Get the component datasheet from the archive.
	mterr = mtar_find(&tar, PECAN_DATASHEET_FILE, &header);
	if (mterr == MTAR_ESUCCESS) {
		mterr = blob_tar_read(&part->datasheet, &tar, header);
		HANDLE_MTAR_ERR(mterr);
	}

cleanup:
	// Clean up our mess.
	free(contents);
	contents = NULL;
	mtar_close(&tar);
	return err;
}

/**
 * Reads an unpacked component archive and populates the archive structure.
 *
 * @param  part Empty component archive to be populated.
 * @param  path Path to the directory of the unpacked component archive.
 * @return      PECAN_OK if the operation was successful.
 *              PECAN_ERR_PATH_NOT_FOUND if the specified path wasn't found.
 *              PECAN_ERR_PARSE if there were parsing errors.
 */
pecan_err_t pecan_read_unpacked(pecan_archive_t *part, const char *path) {
	char *fpath;
	char *contents;
	pecan_err_t err = PECAN_OK;

	// Grab the contents of the manifest attributes file.
	pathcat(2, &fpath, path, PECAN_MANIFEST_FILE);
	contents = slurp_file(fpath);
	free(fpath);
	fpath = NULL;
	if (contents == NULL) {
		err_set_msg(EMSG("Couldn't slurp the contents of the manifest file"));
		return PECAN_ERR_PATH_NOT_FOUND;
	}
	
	// Parse the manifest attributes.
	err = parse_attributes(part, PECAN_MANIFEST, contents);
	free(contents);
	contents = NULL;
	if (err)
		return err;

	// Grab the contents of the attributes file.
	pathcat(2, &fpath, path, PECAN_PARAM_FILE);
	contents = slurp_file(fpath);
	free(fpath);
	fpath = NULL;
	if (contents == NULL) {
		err_set_msg(EMSG("Couldn't slurp the contents of the parameters file"));
		return PECAN_ERR_PATH_NOT_FOUND;
	}

	// Parse the attributes.
	err = parse_attributes(part, PECAN_PARAMETERS, contents);
	free(contents);
	contents = NULL;

	// Slurp the image file.
	pathcat(2, &fpath, path, PECAN_IMAGE_FILE);
	if (file_exists(fpath)) {
		if (blob_slurp(&part->image, fpath) == 0L) {
			err_set_msg(EMSG("Couldn't slurp the contents of the image file"));
			return PECAN_ERR_FILE_IO;
		}
	}
	free(fpath);
	fpath = NULL;

	// Slurp the datasheet file.
	pathcat(2, &fpath, path, PECAN_DATASHEET_FILE);
	if (file_exists(fpath)) {
		if (blob_slurp(&part->datasheet, fpath) == 0L) {
			err_set_msg(EMSG("Couldn't slurp the contents of the datasheet file"));
			return PECAN_ERR_FILE_IO;
		}
	}
	free(fpath);
	fpath = NULL;

	return err;
}

/**
 * Gets the last error message thrown by the library.
 * 
 * @return Last error message string.
 */
const char *pecan_err_msg(void) {
	return err_get_msg();
}

/**
 * Prints the last error message thrown by the library.
 */
void pecan_print_error(void) {
	err_print_msg();
}

/**
 * Pretty prints the contents of an attribute for debugging purposes.
 *
 * @param attr Attribute to be printed.
 */
void pecan_print_attr(pecan_attr_t attr) {
	printf("\"%s\" = \"%s\"", attr.name, attr.value);
}
