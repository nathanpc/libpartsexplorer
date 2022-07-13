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
	printf("=============== Manifest [%zu] ===============\n",
		   pecan_get_attr_len(&part, PECAN_MANIFEST));
	for (idx = 0; idx < pecan_get_attr_len(&part, PECAN_MANIFEST); idx++) {
		pecan_print_attr(*pecan_get_attr_idx(&part, PECAN_MANIFEST, idx));
		printf("\n");
	}

	// Print out its attributes.
	printf("\n=============== Parameters [%zu] ===============\n",
		   pecan_get_attr_len(&part, PECAN_PARAMETERS));
	for (idx = 0; idx < pecan_get_attr_len(&part, PECAN_PARAMETERS); idx++) {
		pecan_print_attr(*pecan_get_attr_idx(&part, PECAN_PARAMETERS, idx));
		printf("\n");
	}

cleanup:
	pecan_free(&part);
	return err;
}
