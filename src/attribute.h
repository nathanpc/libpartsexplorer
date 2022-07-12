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

// Key-Value pair attribute structure definition.
typedef struct {
	char *name;
	char *value;
} pecan_attr_t;

// Initialization
void attr_init(pecan_attr_t *attr);

// Setters
void attr_set_name(pecan_attr_t *attr, const char *name);
void attr_set_name_tk(pecan_attr_t *attr, const char *start, const char *end);
void attr_set_value(pecan_attr_t *attr, const char *value);
void attr_set_value_tk(pecan_attr_t *attr, const char *start, const char *end);

// Cleanup
void attr_free(pecan_attr_t attr);

#ifdef __cplusplus
}
#endif

#endif /* _ATTRIBUTE_H */
