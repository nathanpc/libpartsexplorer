/**
 * attribute.c
 * Collections of utilities to deal with component attributes.
 *
 * @author Nathan Campos <nathan@innoveworkshop.com>
 */

#include "attribute.h"
#include <stdio.h>
#include <string.h>

/**
 * Initializes an component attribute structure.
 * 
 * @param attr Attribute structure to be initialized.
 */
void attr_init(part_attr_t *attr) {
    attr->name = NULL;
    attr->value = NULL;
}

/**
 * Sets the name of the attribute.
 * 
 * @param attr Attribute to be changed.
 * @param name New name of the attribute.
 */
void attr_set_name(part_attr_t *attr, const char *name) {
	//size_t len = strlen()
}


void attr_set_value(part_attr_t *attr, const char *value);

// Cleanup
void attr_free(part_attr_t *attr);
