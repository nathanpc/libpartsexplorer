/**
 * Pecan
 * Virtual electronic components parts bins in your file system.
 *
 * @author Nathan Campos <nathan@innoveworkshop.com>
 */

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

#include "pecan.h"
#ifdef USE_GTK
#	include "gtk/app.h"
#endif

// Command line options structure.
typedef struct {
	bool dump_contents;
	char *output_file;
	char *input_file;
#ifdef HAS_GUI
	bool show_window;
#endif  /* HAS_GUI */
} opts_t;

// Global variables.
static char *prompt = NULL;

// Private methods.
void usage(void);
pecan_err_t dump_archive(pecan_archive_t *part);

/**
 * Program's main entry point.
 *
 * @param  argc Number of command line arguments passed to us.
 * @param  argv Command line arguments.
 * @return      0 on success.
 */
int main(int argc, char **argv) {
	pecan_err_t err;
	pecan_archive_t part;
	opts_t opts;
	char c;

	// Set options defaults.
	err = PECAN_OK;
	prompt = argv[0];
	opterr = 0;
	opts.dump_contents = false;
	opts.output_file = NULL;
#ifdef HAS_GUI
	opts.show_window = true;
#endif  /* HAS_GUI */

	// Go through the command line options.
	while ((c = getopt(argc, argv, "hdwO:")) != -1) {
		switch (c) {
			case 'h':
				// Help the user with usage.
				usage();
				return 0;
			case 'd':
				// Dump contents of the input archive.
				opts.dump_contents = true;
				break;
#ifdef HAS_GUI
			case 'w':
				// Do not show the GUI application.
				opts.show_window = false;
				break;
#endif  /* HAS_GUI */
			case 'O':
				// Set the output file.
				opts.output_file = optarg;
				break;
			case '?':
				// Unknown option or bad argument.
				if (optopt == 'O') {
					fprintf(stderr, "Option -%c requires an argument.\n",
						optopt);
				} else if (isprint(optopt)) {
					fprintf(stderr, "%s: invalid option -- '%c'\n", prompt,
						optopt);
				} else {
					fprintf(stderr, "%s: invalid option character -- '\\x%x'\n",
						prompt, optopt);
				}

				usage();
				return 1;
			default:
				// Die miserably.
				abort();
		}
	}

	// Initialize the archive.
	err = pecan_init(&part);
	if (err)
		goto cleanup;

	// Check if we have an input archive.
	if ((argc - optind) != 1) {
		fprintf(stderr, "An input archive must always be supplied.\n");
		goto cleanup;
	} else {
		opts.input_file = argv[optind];
	}

	// Read the input archive.
	err = pecan_read(&part, opts.input_file);
	if (err)
		goto cleanup;

	// Dump the contents of the archive to stdout?
	if (opts.dump_contents) {
		err = dump_archive(&part);
		if (err)
			goto cleanup;
	}

	// Should we output an archive?
	if (opts.output_file) {
		err = pecan_write(&part, opts.output_file);
		if (err)
			goto cleanup;
	}

#ifdef HAS_GUI
	// Should we show our beautiful GUI application?
	if (opts.show_window) {
		app_main(argc, argv);
	}
#endif  /* HAS_GUI */

cleanup:
	if (err)
		pecan_print_error();
	pecan_free(&part);
	return err;
}

/**
 * Dumps the metadata of an archive to stdout.
 * 
 * @param  part Archive to have its information dumped.
 * @return      PECAN_OK if everything went fine.
 */
pecan_err_t dump_archive(pecan_archive_t *part) {
	size_t idx;

	// Print out its attributes.
	printf("=============== Manifest [%zu] ===============\n",
		   pecan_get_attr_len(part, PECAN_MANIFEST));
	for (idx = 0; idx < pecan_get_attr_len(part, PECAN_MANIFEST); idx++) {
		pecan_print_attr(*pecan_get_attr_idx(part, PECAN_MANIFEST, idx));
		printf("\n");
	}

	// Print out its attributes.
	printf("\n============== Parameters [%zu] ==============\n",
		   pecan_get_attr_len(part, PECAN_PARAMETERS));
	for (idx = 0; idx < pecan_get_attr_len(part, PECAN_PARAMETERS); idx++) {
		pecan_print_attr(*pecan_get_attr_idx(part, PECAN_PARAMETERS, idx));
		printf("\n");
	}

	// Print out the blobs information.
	printf("\n================= Blobs ================\n");
	printf("Image: %zu bytes\n", part->image.len);
	printf("Datasheet: %zu bytes\n", part->datasheet.len);

	return PECAN_OK;
}

/**
 * Displays a helpful usage message.
 */
void usage(void) {
	fprintf(stderr, "usage: %s %s\n\n", prompt, "[-h] [-d] [-O outfile] infile");
	fprintf(stderr, "   -h          Prints out this very helpful message.\n");
	fprintf(stderr, "   -d          Dumps the metadata of an archive to stdout.\n");
	fprintf(stderr, "   -O outfile  Outputs to a new archive.\n");
}
