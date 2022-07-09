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
#define PELIB_EXPORTS extern

// Component archive structure definition.
typedef struct {
    char *fname;
    cvector_vector_type(part_attr_t) attribs;
} cmp_archive_t;

PELIB_EXPORTS int pe_test(void);

#ifdef __cplusplus
}
#endif

#endif /* _PECAN_H */
