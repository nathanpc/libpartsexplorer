/**
 * parser.c
 * Bunch of different parsers to cope with all of the different files inside
 * component archives.
 *
 * @author Nathan Campos <nathan@innoveworkshop.com>
 */

#include "parser.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Parses the attributes INI file and populates the component archive structure.
 *
 * @param  part     Component archive structure.
 * @param  contents Contents of the attributes file.
 * @return          PECAN_OK if the operation was successful.
 *                  PECAN_ERR_PARSE if there were parsing errors.
 */
pecan_err_t parse_attributes(pecan_archive_t *part, const char *contents) {
	printf("%s\n", contents);
	return PECAN_OK;
}
