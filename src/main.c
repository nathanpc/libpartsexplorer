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

	err = pecan_unpacked_read_dir(&part, "example");
	if (err)
		return err;

	return 0;
}
