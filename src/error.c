/**
 * error.c
 * Handles the internal error state of the library.
 * 
 * @author Nathan Campos <nathan@innoveworkshop.com>
 */

#include "error.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// Private variables.
char *pecan_err_msg_buf = NULL;

/**
 * Initializes the error message buffer.
 */
void err_init(void) {
	err_free();
}

/**
 * Sets the error message that the user can later recall.
 *
 * @param msg Error message to be set.
 */
void err_set_msg(const char *msg) {
	// Make sure we have enough space to store our error message.
	pecan_err_msg_buf = (char *)realloc(pecan_err_msg_buf,
										(strlen(msg) + 1) * sizeof(char));

	// Copy the error message.
	strcpy(pecan_err_msg_buf, msg);
}

/**
 * Cleans up the mess left behind by the error message buffer.
 */
void err_free(void) {
	// Free our error string.
	free(pecan_err_msg_buf);
	pecan_err_msg_buf = NULL;
}

/**
 * Gets the last error message thrown by the library.
 *
 * @return Last error message string.
 */
const char *err_get_msg(void) {
	return err_get_msg();
}

/**
 * Prints the last error message thrown by the library.
 */
void err_print_msg(void) {
	printf("ERROR: %s\n", pecan_err_msg_buf);
}
