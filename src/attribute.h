/**
 * attribute.h
 * Collections of utilities to deal with component attributes.
 *
 * @author Nathan Campos <nathan@innoveworkshop.com>
 */

#ifndef _ATTRIBUTE_H
#define _ATTRIBUTE_H

#ifdef __cplusplus
extern "C" {
#endif

#include <cvector.h>

// Key-Value pair attribute structure definition.
typedef struct {
	char *name;
	char *value;
} pecan_attr_t;

// Attribute array type definition.
typedef cvector_vector_type(pecan_attr_t) pecan_attr_arr_t;

// Initialization
void attr_init(pecan_attr_t *attr);

// Setters
void attr_set_name(pecan_attr_t *attr, const char *name);
void attr_set_name_tk(pecan_attr_t *attr, const char *start, const char *end);
void attr_set_value(pecan_attr_t *attr, const char *value);
void attr_set_value_tk(pecan_attr_t *attr, const char *start, const char *end);

// Formatting
size_t attr_get_file_format(pecan_attr_t attr, char **buf);
size_t attr_get_file(pecan_attr_arr_t attribs, char **buf);

// Cleanup
void attr_free(pecan_attr_t attr);

#ifdef __cplusplus
}
#endif

#endif /* _ATTRIBUTE_H */
