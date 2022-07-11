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
	const char *ws = " \t\r";
	const char *delim = "=\r\n";
	const char *sep = "=\n";

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
 * @param  contents Contents of the attributes file.
 * @return          PECAN_OK if the operation was successful.
 *                  PECAN_ERR_PARSE if there were parsing errors.
 */
pecan_err_t parse_attributes(pecan_archive_t *part, const char *contents) {
	const char *start;
	const char *end;
	pecan_attr_t attr;

	// Initialize our attribute structure.
	attr_init(&attr);

	end = contents;
	while (lex_attr(end, &start, &end) != PECAN_OK) {
		const char *tmp = start;
		
		printf("'");
		while (tmp != end) {
			printf("%c", *tmp++);
		}
		printf("' ");
	}
	printf("\n");

	//printf("%s\n", contents);
	return PECAN_OK;
}
