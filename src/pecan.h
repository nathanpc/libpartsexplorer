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
#define PECAN_MANIFEST_FILE  "manifest.ini"
#define PECAN_PARAM_FILE     "parameters.tsv"

// Pecan return status enumeration.
typedef enum {
    PECAN_OK = 0,
	PECAN_ERR_UNKNOWN
} pecan_err_t;

// Component archive structure definition.
typedef struct {
    char *fname;
    cvector_vector_type(pecan_attr_t) attribs;
} pecan_archive_t;

// Initialization
PECAN_EXPORTS pecan_err_t pecan_init(pecan_archive_t *part);

// Read and Write
PECAN_EXPORTS pecan_err_t pecan_read(pecan_archive_t *part, const char *fname);
PECAN_EXPORTS pecan_err_t pecan_write(pecan_archive_t *part, const char *fname);

// Attributes
PECAN_EXPORTS void pecan_add_attr(pecan_archive_t *part, const char *name,
	const char *value);
PECAN_EXPORTS void pecan_set_attr(pecan_archive_t *part, const char *name,
	const char *value);
PECAN_EXPORTS pecan_attr_t *pecan_get_attr(pecan_archive_t *part,
	const char *name);

// Clean up
PECAN_EXPORTS void pecan_free(pecan_archive_t *part);

#ifdef __cplusplus
}
#endif

#endif /* _PECAN_H */
