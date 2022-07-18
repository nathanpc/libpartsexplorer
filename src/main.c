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

// Private function prototypes.
pecan_err_t test_read_unpacked(void);
pecan_err_t test_read_packed(void);

/**
 * Test program main entry point.
 *
 * @param  argc Number of command line arguments passed to us.
 * @param  argv Command line arguments.
 * @return      0 on success.
 */
int main(int argc, char **argv) {
	pecan_err_t err;

	// Perform some basic tests.
	printf("********************* Read Unpacked *********************\n");
	err = test_read_unpacked();
	printf("\n********************* Read Packed *********************\n");
	err = test_read_packed();

	return err;
}

pecan_err_t test_read_unpacked(void) {
	pecan_err_t err;
	pecan_archive_t part;
	size_t idx;

	// Initialize the archive.
	err = pecan_init(&part);
	if (err)
		goto cleanup;

	// Read an unpacked component for testing.
	err = pecan_read_unpacked(&part, "example");
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

	// Print out the blobs information.
	printf("\n=============== Blobs ===============\n");
	printf("Image: %zu bytes\n", part.image.len);
	printf("Datasheet: %zu bytes\n", part.datasheet.len);

	// Write it out just for a simple test.
	pecan_write(&part, "example/example.tar");

cleanup:
	if (err)
		pecan_print_error();
	pecan_free(&part);
	return err;
}

pecan_err_t test_read_packed(void) {
	pecan_err_t err;
	pecan_archive_t part;
	size_t idx;

	// Initialize the archive.
	err = pecan_init(&part);
	if (err)
		goto cleanup;

	// Read an unpacked component for testing.
	err = pecan_read(&part, "example/example.tar");
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

	// Print out the blobs information.
	printf("\n=============== Blobs ===============\n");
	printf("Image: %zu bytes\n", part.image.len);
	printf("Datasheet: %zu bytes\n", part.datasheet.len);

cleanup:
	if (err)
		pecan_print_error();
	pecan_free(&part);
	return err;
}
