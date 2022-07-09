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
} part_attr_t;

// Initialization
void attr_init(part_attr_t *attr);

// Setters
void attr_set_name(part_attr_t *attr, const char *name);
void attr_set_value(part_attr_t *attr, const char *value);

// Cleanup
void attr_free(part_attr_t *attr);

#ifdef __cplusplus
}
#endif

#endif /* _ATTRIBUTE_H */
