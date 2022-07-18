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

#include "attribute.h"
#include "error.h"

// Parsing stages enumerator.
typedef enum {
	PARSING_NAME = 0,
	PARSING_VALUE
} parse_stage_t;

/**
 * A very simple attribute file lexer.
 *
 * @param  str   Input to be lexxed. Feed *end back to keep lexxing.
 * @param  start Pointer to store the start position of the next token.
 * @param  end   Pointer to store the end position of the next token.
 * @return       PECAN_SPECIAL after lexxing each token.
 *               PECAN_OK when there are no new tokens to lex.
 */
pecan_err_t lex_attr(const char *str, const char **start, const char **end) {
	const char *tmp = str;
	const char *ws = " \r";
	const char *delim = "\t\r\n";
	const char *sep = "\t\n";

	// Skip any leading whitespace.
	tmp += strspn(tmp, ws);

	// Check if we are done lexing.
	if (*tmp == '\0') {
		*start = *end = NULL;
		return PECAN_OK;
	}

	// Set the starting point of our token.
	*start = tmp;
	
	// Check if the token is just a separator.
	if (strchr(sep, *tmp) != NULL) {
		*end = tmp + 1;
		return PECAN_SPECIAL;
	}

	// Find the end of the token.
	*end = tmp + strcspn(tmp, delim);
	return PECAN_SPECIAL;
}

/**
 * Parses the attributes INI file and populates the component archive structure.
 *
 * @param  part     Component archive structure.
 * @param  type     Type of attribute.
 * @param  contents Contents of the attributes file.
 * @return          PECAN_OK if the operation was successful.
 *                  PECAN_ERR_PARSE if there were parsing errors.
 */
pecan_err_t parse_attributes(pecan_archive_t *part, pecan_attr_type_t type,
							 const char *contents) {
	parse_stage_t stage;
	pecan_attr_t attr;
	const char *start;
	const char *end;

	// Initialize our attribute structure.
	attr_init(&attr);

	// Lex the contents and parse out the attributes.
	stage = PARSING_NAME;
	end = contents;
	while (lex_attr(end, &start, &end) != PECAN_OK) {
		switch (stage) {
		case PARSING_NAME:
			// Parsing the attribute name.
			if (*start == '\t') {
				stage = PARSING_VALUE;
				continue;
			}

			attr_set_name_tk(&attr, start, end);
			break;
		case PARSING_VALUE:
			if (*start == '\n') {
				pecan_add_attr(part, type, attr);
				attr_init(&attr);

				stage = PARSING_NAME;
				continue;
			}

			// TODO: Concatenate the values until a newline.
			attr_set_value_tk(&attr, start, end);
			break;
		}
	}

	return PECAN_OK;
}
