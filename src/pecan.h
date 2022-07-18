/**
 * pecan.h
 * The helper library to deal with your electronic components definitions.
 *
 * @author Nathan Campos <nathan@innoveworkshop.com>
 */

#ifndef _PECAN_H
#define _PECAN_H

#ifdef __cplusplus
extern "C" {
#endif

#include <cvector.h>
#include <microtar.h>

#include "attribute.h"

// Library export definition.
#define PECAN_EXPORTS extern

// File name definitions.
#define PECAN_DATASHEET_FILE "datasheet.pdf"
#define PECAN_IMAGE_FILE     "image.bmp"
#define PECAN_MANIFEST_FILE  "manifest.tsv"
#define PECAN_PARAM_FILE     "parameters.tsv"

// Attributes switch enumeration.
typedef enum {
	PECAN_MANIFEST = 0,
	PECAN_PARAMETERS
} pecan_attr_type_t;

// Pecan return status enumeration.
typedef enum {
	PECAN_SPECIAL = -100,
	PECAN_OK = 0,
	PECAN_ERR_PATH_NOT_FOUND,
	PECAN_ERR_FILE_IO,
	PECAN_ERR_PARSE,
	PECAN_ERR_UNKNOWN,
	PECAN_ERR_NOT_IMPLEMENTED
} pecan_err_t;

// Component archive structure definition.
typedef struct {
	char *fname;
	pecan_attr_arr_t attribs;
	pecan_attr_arr_t params;
} pecan_archive_t;

// Initialization
PECAN_EXPORTS pecan_err_t pecan_init(pecan_archive_t *part);

// Generic Archive Read
PECAN_EXPORTS pecan_err_t pecan_read(pecan_archive_t *part, const char *fpath);

// Specific Read and Write
PECAN_EXPORTS pecan_err_t pecan_read_packed(pecan_archive_t *part,
											const char *fname);
PECAN_EXPORTS pecan_err_t pecan_read_unpacked(pecan_archive_t *part,
											  const char *path);
PECAN_EXPORTS pecan_err_t pecan_write(pecan_archive_t *part, const char *fname);

// Attributes
PECAN_EXPORTS void pecan_add_attr(pecan_archive_t *part, pecan_attr_type_t type,
								  pecan_attr_t attr);
PECAN_EXPORTS void pecan_add_attr_str(pecan_archive_t *part,
									  pecan_attr_type_t type, const char *name,
									  const char *value);
PECAN_EXPORTS void pecan_set_attr(pecan_archive_t *part, pecan_attr_type_t type,
								  const char *name, const char *value);
PECAN_EXPORTS pecan_attr_t *pecan_get_attr(pecan_archive_t *part,
										   pecan_attr_type_t type,
										   const char *name);
PECAN_EXPORTS pecan_attr_t *pecan_get_attr_idx(pecan_archive_t *part,
											   pecan_attr_type_t type,
											   size_t index);
PECAN_EXPORTS size_t pecan_get_attr_len(pecan_archive_t *part,
										pecan_attr_type_t type);

// Clean up
PECAN_EXPORTS void pecan_free(pecan_archive_t *part);

// Debugging
PECAN_EXPORTS void pecan_print_attr(pecan_attr_t attr);

#ifdef __cplusplus
}
#endif

#endif /* _PECAN_H */
