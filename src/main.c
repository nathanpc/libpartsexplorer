/**
 * Pecan Library Test
 * A very simple test for the pecan library.
 *
 * @author Nathan Campos <nathan@innoveworkshop.com>
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "pecan.h"
#include "fileutils.h"

/**
 * Test program main entry point.
 * 
 * @param  argc Number of command line arguments passed to us.
 * @param  argv Command line arguments.
 * @return      0 on success.
 */
int main(int argc, char **argv) {
	pecan_err_t err;
	pecan_archive_t part;
	size_t idx;

	// Initialize the archive.
	pecan_init(&part);

	// Read an unpacked component for testing.
	err = pecan_unpacked_read_dir(&part, "example");
	if (err)
		goto cleanup;

	// Print out its attributes.
	for (idx = 0; idx < pecan_get_attr_len(&part); idx++) {
		pecan_print_attr(*pecan_get_attr_idx(&part, idx));
		printf("\n");
	}

cleanup:
	pecan_free(&part);
	return err;
}
