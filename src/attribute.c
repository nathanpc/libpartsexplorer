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
	attr->name = (char *)realloc(attr->name, (strlen(name) + 1) * sizeof(char));

	// Actually set the attribute.
	strcpy(attr->name, name);
}

/**
 * Sets the name of the attribute.
 *
 * @param attr  Attribute to be changed.
 * @param value New value of the attribute.
 */
void attr_set_value(pecan_attr_t *attr, const char *value) {
	// Make sure we have enough space to store our attribute.
	attr->value = (char *)realloc(attr->value,
								  (strlen(value) + 1) * sizeof(char));

	// Actually set the attribute.
	strcpy(attr->value, value);
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
